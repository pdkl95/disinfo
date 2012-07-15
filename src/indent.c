#include "common.h"
#include "indent.h"

int   istate_total = 0;
int   istate_depth = 0;
int   istate_depth_max = 0;
char *istate_depth_string = NULL;
int   istate_env   = 0;
char *istate_env_str = NULL;

static uid_t uid;
static pid_t pid;
static pid_t ppid;

static char *istate_dir;
static char *istate_file;


bool
indent_state_init(void)
{
    size_t len;
    char *p;

    if (istate_depth_string) {
        return true;
    }

    istate_env_str = getenv(ENVNAME_ADD_INDENT);
    if (istate_env_str) {
        istate_env = atoi(istate_env_str);
    } else {
        istate_env = 0;
    }
    if (istate_env > INDENT_MAX) {
        istate_env = INDENT_MAX;
    }
    istate_depth_max = INDENT_MAX - istate_env;

    uid  = getuid();
    pid  = getpid();
    ppid = getppid();
    /* printf("uid=%d ppid=%d pid=%d\n", uid, ppid, pid); */

    if (asprintf(&istate_dir, "/tmp/.disinfo-%d", uid) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_init;
    }

    if (!isdir(istate_dir)) {
        if (!mkdir(istate_dir, 0700)) {
            derror("disinfo: mkdir(%s, 0700) faild: %s", istate_dir, strerror(errno));
        }
    }

    if (asprintf(&istate_file, "%s/indent-%d", istate_dir, ppid) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_init;
    }
    /* printf("file=\"%s\"\n", istate_file); */

    p = read_file(istate_file, &len);
    if ((len < 1) || !p || (*p == '\0')) {
        goto fail_istate_init;
    }

    /* printf("%d byptes, [%s]\n", (int)len, p); */

    istate_depth = atoi(p);
    istate_depth_string = p;
    /* printf("depth = %d\n", istate_depth); */

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

    /* printf("SAVE: %s value %d\n", istate_file, istate_depth); */

    if (!istate_file) {
        dwarn("disinfo: no filename to save to! indent will fail!");
        goto fail_istate_save;
    }

    if (istate_depth < 1) {
        /* dinfo("disinfo: istate_depth<1 -> jumpinto to unlink()"); */
        goto fail_istate_save;
    }

    fd = open(istate_file, O_WRONLY|O_TRUNC|O_CREAT, S_IRUSR|S_IWUSR);
    if (!fd) {
        derror("disinfo: open() failed: %s", strerror(errno));
        goto fail_istate_save;
    }

    if (asprintf(&p, "%02d", istate_depth) < 0) {
        derror("disinfo: asprintf failed: %s", strerror(errno));
        goto fail_istate_save;
    }
    /* printf("p=\"%s\"\n", p); */
    if (full_write(fd, p, strlen(p)) < strlen(p)) {
        derror("disinfo: write to failed: %s", strerror(errno));
        goto fail_istate_save;
    }

    close(fd);
    return 0;

  fail_istate_save:
    unlink(istate_file);
    /* if (unlink(istate_file)) { */
    /*     derror("Unlink failed for: %s", istate_file); */
    /* } */
    return 0;
}

int
dindent(void)
{
    indent_state_init();

    istate_depth += 1;
    if (istate_depth > istate_depth_max) {
        istate_depth = istate_depth_max;
    }

    return indent_state_save();
}

int
doutdent(void)
{
    indent_state_init();

    istate_depth -= 1;
    if (istate_depth < 0) {
        istate_depth = 0;
    }

    return indent_state_save();
}

int
get_indent(void)
{
    indent_state_init();
    return istate_depth + istate_env;
}
