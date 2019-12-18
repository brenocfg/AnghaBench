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
struct TYPE_3__ {int wind_type; int /*<<< orphan*/  f_kaiser_alpha; } ;
typedef  TYPE_1__ window_param ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int NB_WINDOWS ; 
 int NONE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_InheritFloat (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * window_list ; 

void window_get_param( vlc_object_t * p_aout, window_param * p_param )
{
    /* Fetch Kaiser parameter */
    p_param->f_kaiser_alpha = var_InheritFloat( p_aout, "effect-kaiser-param" );

    /* Fetch window type */
    char * psz_preset = var_InheritString( p_aout, "effect-fft-window" );
    if( !psz_preset )
    {
        goto no_preset;
    }

    for( int i = 0; i < NB_WINDOWS; i++ )
    {
        if( !strcasecmp( psz_preset, window_list[i] ) )
        {
            free( psz_preset );
            p_param->wind_type = i;
            return;
        }
    }
    free( psz_preset );

no_preset:
    msg_Warn( p_aout, "No matching window preset found; using rectangular "
                      "window (i.e. no window)" );
    p_param->wind_type = NONE;
}