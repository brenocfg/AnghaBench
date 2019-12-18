#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct vlclua_playlist {struct vlclua_playlist* access; int /*<<< orphan*/ * L; struct vlclua_playlist* filename; } ;
struct TYPE_2__ {struct vlclua_playlist* p_sys; } ;
typedef  TYPE_1__ stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlclua_playlist*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 

void Close_LuaPlaylist(vlc_object_t *obj)
{
    stream_t *s = (stream_t *)obj;
    struct vlclua_playlist *sys = s->p_sys;

    free(sys->filename);
    assert(sys->L != NULL);
    lua_close(sys->L);
    free(sys->access);
    free(sys);
}