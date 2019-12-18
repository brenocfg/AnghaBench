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
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_buf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_dyups_do_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_dyups_do_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_string (char*) ; 

__attribute__((used)) static ngx_int_t
ngx_dyups_sandbox_update(ngx_buf_t *buf, ngx_str_t *rv)
{
    ngx_int_t  rc;
    ngx_str_t  dumy;

    ngx_str_t  sandbox = ngx_string("_dyups_upstream_sandbox_");

    rc = ngx_dyups_do_update(&sandbox, buf, rv);

    (void) ngx_dyups_do_delete(&sandbox, &dumy);

    return rc;
}