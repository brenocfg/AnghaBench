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
struct TYPE_3__ {int i_cmd_w; int i_cmd_max; int /*<<< orphan*/ * p_cmd; } ;
typedef  TYPE_1__ ts_storage_t ;
typedef  int /*<<< orphan*/  ts_cmd_t ;

/* Variables and functions */
 int __MAX (int,int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void TsStoragePack( ts_storage_t *p_storage )
{
    /* Try to release a bit of memory */
    if( p_storage->i_cmd_w >= p_storage->i_cmd_max )
        return;

    p_storage->i_cmd_max = __MAX( p_storage->i_cmd_w, 1 );

    ts_cmd_t *p_new = realloc( p_storage->p_cmd, p_storage->i_cmd_max * sizeof(*p_storage->p_cmd) );
    if( p_new )
        p_storage->p_cmd = p_new;
}