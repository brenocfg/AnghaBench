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
struct TYPE_3__ {unsigned int fdc; int* fdv; } ;
typedef  TYPE_1__ vlclua_dtable_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* vlclua_get_dtable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_fd_get( lua_State *L, unsigned idx )
{
    vlclua_dtable_t *dt = vlclua_get_dtable( L );

    if( idx < 3u )
        return idx;
    idx -= 3;
    return (idx < dt->fdc) ? dt->fdv[idx] : -1;
}