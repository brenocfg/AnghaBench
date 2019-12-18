#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {scalar_t__ fd; int /*<<< orphan*/  name; int /*<<< orphan*/  log; } ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  offset; TYPE_3__ file; scalar_t__ thread_write; int /*<<< orphan*/  warn; scalar_t__ log_level; int /*<<< orphan*/  access; int /*<<< orphan*/  clean; int /*<<< orphan*/  persistent; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ ngx_temp_file_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
 scalar_t__ NGX_INVALID_FILE ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_create_temp_file (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_thread_write_chain_to_file (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_write_chain_to_file (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t
ngx_write_chain_to_temp_file(ngx_temp_file_t *tf, ngx_chain_t *chain)
{
    ngx_int_t  rc;

    if (tf->file.fd == NGX_INVALID_FILE) {
        rc = ngx_create_temp_file(&tf->file, tf->path, tf->pool,
                                  tf->persistent, tf->clean, tf->access);

        if (rc != NGX_OK) {
            return rc;
        }

        if (tf->log_level) {
            ngx_log_error(tf->log_level, tf->file.log, 0, "%s %V",
                          tf->warn, &tf->file.name);
        }
    }

#if (NGX_THREADS && NGX_HAVE_PWRITEV)

    if (tf->thread_write) {
        return ngx_thread_write_chain_to_file(&tf->file, chain, tf->offset,
                                              tf->pool);
    }

#endif

    return ngx_write_chain_to_file(&tf->file, chain, tf->offset, tf->pool);
}