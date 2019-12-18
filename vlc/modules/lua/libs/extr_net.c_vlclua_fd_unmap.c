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
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* vlclua_get_dtable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlclua_fd_unmap( lua_State *L, unsigned idx )
{
    vlclua_dtable_t *dt = vlclua_get_dtable( L );
    int fd;

    if( idx < 3u )
        return; /* Never close stdin/stdout/stderr. */

    idx -= 3;
    if( idx >= dt->fdc )
        return;

    fd = dt->fdv[idx];
    dt->fdv[idx] = -1;
    while( dt->fdc > 0 && dt->fdv[dt->fdc - 1] == -1 )
        dt->fdc--;
    /* realloc() not really needed */
#ifndef NDEBUG
    for( unsigned i = 0; i < dt->fdc; i++ )
        assert( dt->fdv[i] != fd );
#else
    (void) fd;
#endif
}