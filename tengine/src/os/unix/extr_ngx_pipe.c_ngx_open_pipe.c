#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ ngx_pid_t ;
struct TYPE_15__ {int* pfd; int type; TYPE_3__* argv; TYPE_2__* open_fd; scalar_t__ pid; } ;
typedef  TYPE_4__ ngx_open_pipe_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_5__ ngx_cycle_t ;
struct TYPE_17__ {int /*<<< orphan*/  user; int /*<<< orphan*/  group; int /*<<< orphan*/  username; } ;
typedef  TYPE_6__ ngx_core_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ ** elts; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {scalar_t__ fd; TYPE_1__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_FILE_ERROR ; 
 int /*<<< orphan*/  NGX_FILE_OPEN ; 
 int /*<<< orphan*/  NGX_FILE_WRONLY ; 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_PIPE_WRITE ; 
 int /*<<< orphan*/  NGX_PROCESS_PIPE ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int close (int) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  execv (char const*,char* const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ geteuid () ; 
 int initgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_close_listening_sockets (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int ngx_open_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_pipe_log (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_process ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ pipe (int*) ; 
 int setgid (int /*<<< orphan*/ ) ; 
 int setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_open_pipe(ngx_cycle_t *cycle, ngx_open_pipe_t *op)
{
    int               fd;
    u_char          **argv;
    ngx_pid_t         pid;
    sigset_t          set;
#ifdef T_PIPE_USE_USER
    ngx_core_conf_t  *ccf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);
#endif

    if (pipe(op->pfd) < 0) {
        return NGX_ERROR;
    }

    argv = op->argv->elts;

    if ((pid = fork()) < 0) {
        goto err;
    } else if (pid > 0) {
        op->pid = pid;

        if (op->open_fd->fd != NGX_INVALID_FILE) {
            if (close(op->open_fd->fd) == NGX_FILE_ERROR) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "close \"%s\" failed",
                              op->open_fd->name.data);
            }
        }

        if (op->type == NGX_PIPE_WRITE) {
            op->open_fd->fd = op->pfd[1];
            close(op->pfd[0]);
        } else {
            op->open_fd->fd = op->pfd[0];
            close(op->pfd[1]);
        }
    } else {

       /*
        * Set correct process type since closing listening Unix domain socket
        * in a master process also removes the Unix domain socket file.
        */
        ngx_process = NGX_PROCESS_PIPE;
        ngx_close_listening_sockets(cycle);

        if (op->type == 1) {
            close(op->pfd[1]);
            if (op->pfd[0] != STDIN_FILENO) {
                dup2(op->pfd[0], STDIN_FILENO);
                close(op->pfd[0]);
            }
        } else {
            close(op->pfd[0]);
            if (op->pfd[1] != STDOUT_FILENO) {
                dup2(op->pfd[1], STDOUT_FILENO);
                close(op->pfd[1]);
            }
        }
#ifdef T_PIPE_USE_USER
        if (geteuid() == 0) {
            if (setgid(ccf->group) == -1) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "setgid(%d) failed", ccf->group);
                exit(2);
            }

            if (initgroups(ccf->username, ccf->group) == -1) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "initgroups(%s, %d) failed",
                              ccf->username, ccf->group);
            }

            if (setuid(ccf->user) == -1) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "setuid(%d) failed", ccf->user);
                exit(2);
            }
        }
#endif

        /*
         * redirect stderr to /dev/null, because stderr will be connected with
         * fd used by the last pipe when error log is configured using pipe,
         * that will cause it no close
         */

        fd = ngx_open_file("/dev/null", NGX_FILE_WRONLY, NGX_FILE_OPEN, 0);
        if (fd == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "open(\"/dev/null\") failed");
            exit(2);
        }

        if (dup2(fd, STDERR_FILENO) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "dup2(STDERR) failed");
            exit(2);
        }

        if (fd > STDERR_FILENO && close(fd) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "close() failed");
            exit(2);
        }

        sigemptyset(&set);

        if (sigprocmask(SIG_SETMASK, &set, NULL) == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "sigprocmask() failed");
            exit(2);
        }

        if (ngx_strncmp(argv[0], "rollback", sizeof("rollback") - 1) == 0) {
            ngx_pipe_log(cycle, op);
            exit(0);

        } else {
            execv((const char *) argv[0], (char *const *) op->argv->elts);
            exit(0);
        }
    }

    return NGX_OK;

err:

    close(op->pfd[0]);
    close(op->pfd[1]);

    return NGX_ERROR;
}