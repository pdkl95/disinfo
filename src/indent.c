#include "common.h"
#include "indent.h"

int  istate_depth;
char istate_depth_string[ISTATE_BUFLEN];


static uid_t uid;
static pid_t pid;
static pid_t ppid;
static char *istate_dir;
static char *istate_file;
static int   istate_fd;


bool
indent_state_init(void)
{
    int len;

    uid = getuid();
    pid = getpid();
    ppid = getppid();

    if (asprintf(&istate_dir, "/tmp/.disinfo-%d", uid)) {
        die("disinfo: asprintf failed");
    }
    if (asprintf(&istate_file, "%s/indent-%d", istate_dir, ppid)) {
        die("disinfo: asprintf failed");
    }

    istate_fd = open(istate_file, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

    if (!istate_fd) {
        perror("disinfo: error opening indent-state file");
        return false;
    }

    len = read(istate_fd, istate_depth_string, ISTATE_DEPTH_DIGITS);

    istate_depth_string[ISTATE_DEPTH_DIGITS] = '\0';
    istate_depth = atoi(istate_depth_string);

    return true;
}

void
indent_state_save(void)
{
    if (lseek(istate_fd, 0, SEEK_SET) < 0) {
        die("lseek failed");
    }
    if (ftruncate(istate_fd, 0)) {
        die("disinfo: ftruncate failed");
    }

    sprintf(istate_depth_string, "%02d", istate_depth);

    write(istate_fd, istate_depth_string, ISTATE_DEPTH_DIGITS);

    close(istate_fd);
}


int
get_current_indent(void)
{
    return 0;
}

int
dindent(void)
{
    return 0;
}

int
doutdent(void)
{
    return 0;
}
