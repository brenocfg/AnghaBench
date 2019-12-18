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
typedef  int /*<<< orphan*/  luabatch_context_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ demux_meta_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_meta( vlc_object_t *p_this, const char * psz_filename,
                      const luabatch_context_t *p_context )
{
    /* FIXME: merge with finder */
    demux_meta_t *p_demux_meta = (demux_meta_t *)p_this;
    VLC_UNUSED( p_context );

    lua_State *L = init( p_this, p_demux_meta->p_item, psz_filename );
    if( !L )
        return VLC_EGENERIC;

    int i_ret = run(p_this, psz_filename, L, "read_meta", NULL);
    lua_close( L );

    // Continue even if an error occurred: all "meta reader" are always run.
    return i_ret == VLC_SUCCESS ? VLC_EGENERIC : i_ret;
}