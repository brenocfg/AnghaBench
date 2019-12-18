#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_item; } ;
typedef  TYPE_1__ luabatch_context_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/ * init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char*,TYPE_1__ const*) ; 

__attribute__((used)) static int fetch_meta( vlc_object_t *p_this, const char * psz_filename,
                       const luabatch_context_t *p_context )
{
    lua_State *L = init( p_this, p_context->p_item, psz_filename );
    if( !L )
        return VLC_EGENERIC;

    int ret = run(p_this, psz_filename, L, "fetch_meta", p_context);
    lua_close( L );

    return ret;
}