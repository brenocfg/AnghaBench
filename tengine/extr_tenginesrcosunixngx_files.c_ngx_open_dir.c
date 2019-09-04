#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {scalar_t__ valid_info; int /*<<< orphan*/ * dir; } ;
typedef  TYPE_2__ ngx_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * opendir (char const*) ; 

ngx_int_t
ngx_open_dir(ngx_str_t *name, ngx_dir_t *dir)
{
    dir->dir = opendir((const char *) name->data);

    if (dir->dir == NULL) {
        return NGX_ERROR;
    }

    dir->valid_info = 0;

    return NGX_OK;
}