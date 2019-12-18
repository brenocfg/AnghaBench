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
struct TYPE_4__ {int b_bool; int /*<<< orphan*/  i_int; int /*<<< orphan*/  f_float; int /*<<< orphan*/  psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int VLC_ENOOBJ ; 
 scalar_t__ VLC_SUCCESS ; 
#define  VLC_VAR_ADDRESS 132 
#define  VLC_VAR_BOOL 131 
 int VLC_VAR_CLASS ; 
#define  VLC_VAR_FLOAT 130 
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 int /*<<< orphan*/  config_GetFloat (char const*) ; 
 int /*<<< orphan*/  config_GetInt (char const*) ; 
 int /*<<< orphan*/  config_GetPsz (char const*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ var_GetChecked (int /*<<< orphan*/ *,char const*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/ * vlc_object_parent (int /*<<< orphan*/ *) ; 

int var_Inherit( vlc_object_t *p_this, const char *psz_name, int i_type,
                 vlc_value_t *p_val )
{
    i_type &= VLC_VAR_CLASS;
    for (vlc_object_t *obj = p_this; obj != NULL; obj = vlc_object_parent(obj))
    {
        if( var_GetChecked( obj, psz_name, i_type, p_val ) == VLC_SUCCESS )
            return VLC_SUCCESS;
    }

    /* else take value from config */
    switch( i_type & VLC_VAR_CLASS )
    {
        case VLC_VAR_STRING:
            p_val->psz_string = config_GetPsz( psz_name );
            if( !p_val->psz_string ) p_val->psz_string = strdup("");
            break;
        case VLC_VAR_FLOAT:
            p_val->f_float = config_GetFloat( psz_name );
            break;
        case VLC_VAR_INTEGER:
            p_val->i_int = config_GetInt( psz_name );
            break;
        case VLC_VAR_BOOL:
            p_val->b_bool = config_GetInt( psz_name ) > 0;
            break;
        default:
            vlc_assert_unreachable();
        case VLC_VAR_ADDRESS:
            return VLC_ENOOBJ;
    }
    return VLC_SUCCESS;
}