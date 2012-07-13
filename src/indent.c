#include "common.h"
#include "indent.h"

int   istate_depth = 0;
char *istate_depth_string = NULL;


static uid_t uid;
static pid_t pid;
static pid_t ppid;

static char *istate_dir;
static char *istate_file;



bool
indent_state_init(void)
{
    size_t len;

    if (istate_depth_string) {
        return true;
    }

    uid  = getuid();
    pid  = getpid();
    ppid = getppid();
    printf("uid=%d ppid=%d pid=%d", uid, ppid, pid);

    if (asprintf(&istate_dir, "/tmp/.disinfo-%d", uid) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_init;
    }

    if (!isdir(istate_dir)) {
        mkdir(istate_dir, 0700);
    }

    if (asprintf(&istate_file, "%s/indent-%d", istate_dir, ppid) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_init;
    }
    printf("%s [good]\n", istate_file);

    istate_depth_string = read_file(istate_file, &len);
    if ((len < 1) ||
        !istate_depth_string ||
        (istate_depth_string[0] == '\0')) {
        goto fail_istate_init;
    }


    printf("[%s]\n", istate_depth_string);
    istate_depth = atoi(istate_depth_string);
    return true;

  fail_istate_init:
    istate_depth_string = "00";
    istate_depth = 0;
    return false;
}

int
indent_state_save(void)
{
    int fd;
    char *p;
    if (!istate_file) {
        goto fail_istate_save;
    }

    if (istate_depth < 1) {
        goto fail_istate_save;
    }

    fd = open(istate_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
    if (!fd) {
        derror("disinfo: open() failed: %s", strerror(errno));
    }

    if (asprintf(&p, "%02d", istate_depth) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_save;
    }

    if (full_write(fd, istate_depth_string, strlen(p)) < strlen(p)) {
        derror("disinfo: write to failed: %s", strerror(errno));

    }

    close(fd);
    return 0;

  fail_istate_save:
    if (unlink(istate_file)) {
        derror("Unlink failed for: %s", istate_file);
    }
    return 0;
}

int
dindent(void)
{
    istate_depth += 1;
    if (istate_depth > INDENT_MAX) {
        istate_depth = INDENT_MAX;
    }

    return indent_state_save();
}

int
doutdent(void)
{
    istate_depth -= 1;
    if (istate_depth < 0) {
        istate_depth = 0;
    }

    return indent_state_save();
}


void
indent_common_options(int *argc, char **argv[])
{
    common_options(argc, argv);
    indent_state_init();
}
