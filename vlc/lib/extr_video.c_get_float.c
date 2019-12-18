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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ opt_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 scalar_t__ VLC_VAR_FLOAT ; 
 int /*<<< orphan*/  libvlc_printerr (char*,char const*,char*) ; 
 float var_GetFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float
get_float( libvlc_media_player_t *p_mi, const char *restrict name,
            const opt_t *restrict opt )
{
    if( !opt ) return 0.0;

    if( opt->type != VLC_VAR_FLOAT )
    {
        libvlc_printerr( "Invalid argument to %s in %s", name, "get float" );
        return 0.0;
    }

    return var_GetFloat( p_mi, opt->name );
}