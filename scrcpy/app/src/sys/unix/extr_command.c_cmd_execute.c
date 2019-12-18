#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ret ;
typedef  int pid_t ;
typedef  enum process_result { ____Placeholder_process_result } process_result ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int PROCESS_ERROR_GENERIC ; 
 int PROCESS_ERROR_MISSING_BINARY ; 
 int PROCESS_SUCCESS ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execvp (char const*,char* const*) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pipe (int*) ; 
 int read (int,int*,int) ; 
 int write (int,int*,int) ; 

enum process_result
cmd_execute(const char *path, const char *const argv[], pid_t *pid) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return PROCESS_ERROR_GENERIC;
    }

    enum process_result ret = PROCESS_SUCCESS;

    *pid = fork();
    if (*pid == -1) {
        perror("fork");
        ret = PROCESS_ERROR_GENERIC;
        goto end;
    }

    if (*pid > 0) {
        // parent close write side
        close(fd[1]);
        fd[1] = -1;
        // wait for EOF or receive errno from child
        if (read(fd[0], &ret, sizeof(ret)) == -1) {
            perror("read");
            ret = PROCESS_ERROR_GENERIC;
            goto end;
        }
    } else if (*pid == 0) {
        // child close read side
        close(fd[0]);
        if (fcntl(fd[1], F_SETFD, FD_CLOEXEC) == 0) {
            execvp(path, (char *const *)argv);
            if (errno == ENOENT) {
                ret = PROCESS_ERROR_MISSING_BINARY;
            } else {
                ret = PROCESS_ERROR_GENERIC;
            }
            perror("exec");
        } else {
            perror("fcntl");
            ret = PROCESS_ERROR_GENERIC;
        }
        // send ret to the parent
        if (write(fd[1], &ret, sizeof(ret)) == -1) {
            perror("write");
        }
        // close write side before exiting
        close(fd[1]);
        _exit(1);
    }

end:
    if (fd[0] != -1) {
        close(fd[0]);
    }
    if (fd[1] != -1) {
        close(fd[1]);
    }
    return ret;
}