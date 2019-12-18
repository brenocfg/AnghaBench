#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vout_thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  psz_string; int /*<<< orphan*/  i_int; } ;
typedef  TYPE_1__ vlc_value_t ;
struct TYPE_7__ {int type; char* name; } ;
typedef  TYPE_2__ opt_t ;
typedef  int /*<<< orphan*/  libvlc_media_player_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** GetVouts (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
#define  VLC_VAR_FLOAT 130 
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int get_filter_str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libvlc_printerr (char*,char const*) ; 
 int /*<<< orphan*/  var_SetChecked (int /*<<< orphan*/ *,char const*,int,TYPE_1__) ; 
 int /*<<< orphan*/  var_TriggerCallback (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_value( libvlc_media_player_t *p_mi, const char *restrict name,
           const opt_t *restrict opt, unsigned i_expected_type,
           const vlc_value_t *val, bool b_sub_source )
{
    if( !opt ) return;

    int i_type = opt->type;
    vlc_value_t new_val = *val;
    const char *psz_opt_name = opt->name;
    switch( i_type )
    {
        case 0: /* the enabler */
        {
            int i_ret = get_filter_str( VLC_OBJECT( p_mi ), opt->name, val->i_int,
                                        &psz_opt_name, &new_val.psz_string );
            if( i_ret != VLC_SUCCESS )
                return;
            i_type = VLC_VAR_STRING;
            break;
        }
        case VLC_VAR_INTEGER:
        case VLC_VAR_FLOAT:
        case VLC_VAR_STRING:
            if( i_expected_type != opt->type )
            {
                libvlc_printerr( "Invalid argument to %s", name );
                return;
            }
            break;
        default:
            libvlc_printerr( "Invalid argument to %s", name );
            return;
    }

    /* Set the new value to the media player. Next vouts created from this
     * media player will inherit this new value */
    var_SetChecked( p_mi, psz_opt_name, i_type, new_val );

    /* Set the new value to every loaded vouts */
    size_t i_vout_count;
    vout_thread_t **pp_vouts = GetVouts( p_mi, &i_vout_count );
    for( size_t i = 0; i < i_vout_count; ++i )
    {
        var_SetChecked( pp_vouts[i], psz_opt_name, i_type, new_val );
        if( b_sub_source )
            var_TriggerCallback( pp_vouts[i], "sub-source" );
        vout_Release(pp_vouts[i]);
    }

    if( opt->type == 0 )
        free( new_val.psz_string );
}