#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_file_info_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_PIPE_DIR_ACCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ngx_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 scalar_t__ ngx_file_info (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void
ngx_pipe_create_subdirs(char *filename, ngx_cycle_t *cycle)
{
    ngx_file_info_t stat_buf;
    char            dirname[1024];
    char           *p;

    for (p = filename; (p = strchr(p, '/')); p++)
    {
        if (p == filename) {
            continue;       // Don't bother with the root directory
        }

        ngx_memcpy(dirname, filename, p - filename);
        dirname[p-filename] = '\0';

        if (ngx_file_info(dirname, &stat_buf) < 0) {
            if (errno != ENOENT) {
                ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                              "stat [%s] failed", dirname);
                exit(2);

            } else {
                if ((ngx_create_dir(dirname, NGX_PIPE_DIR_ACCESS) < 0) && (errno != EEXIST)) {
                    ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                                  "mkdir [%s] failed", dirname);
                    exit(2);
                }
            }
        }
    }
}