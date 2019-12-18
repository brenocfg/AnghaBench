#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {scalar_t__ type; TYPE_2__* de; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ ngx_dir_t ;
struct TYPE_5__ {scalar_t__ d_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* readdir (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_read_dir(ngx_dir_t *dir)
{
    dir->de = readdir(dir->dir);

    if (dir->de) {
#if (NGX_HAVE_D_TYPE)
        dir->type = dir->de->d_type;
#else
        dir->type = 0;
#endif
        return NGX_OK;
    }

    return NGX_ERROR;
}