#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {char* psz_string; } ;
typedef  TYPE_2__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_30__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_31__ {int i_band; float* f_alpha; float* f_beta; float* f_gamma; int b_2eqz; float f_gamp; float* f_amp; float** x; float** x2; float*** y; float*** y2; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_32__ {int i_band; TYPE_1__* band; } ;
typedef  TYPE_5__ eqz_config_t ;
struct TYPE_28__ {float f_alpha; float f_beta; float f_gamma; int /*<<< orphan*/  f_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  BandsCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__,TYPE_4__*) ; 
 int /*<<< orphan*/  EqzCoeffs (int,float,int,TYPE_5__*) ; 
 int /*<<< orphan*/  PreampCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__,TYPE_4__*) ; 
 int /*<<< orphan*/  PresetCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__,TYPE_4__*) ; 
 int /*<<< orphan*/  TwoPassCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__,TYPE_4__*) ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int VLC_SUCCESS ; 
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_FLOAT ; 
 int VLC_VAR_STRING ; 
 int /*<<< orphan*/  free (float*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,float,float,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  var_AddCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__,TYPE_2__,TYPE_4__*),TYPE_4__*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int) ; 
 int var_CreateGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_Get (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 void* vlc_alloc (int,int) ; 
 int /*<<< orphan*/ * vlc_object_parent (TYPE_3__*) ; 

__attribute__((used)) static int EqzInit( filter_t *p_filter, int i_rate )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    eqz_config_t cfg;
    int i, ch;
    vlc_value_t val1, val2, val3;
    vlc_object_t *p_aout = vlc_object_parent(p_filter);
    int i_ret = VLC_ENOMEM;

    bool b_vlcFreqs = var_InheritBool( p_aout, "equalizer-vlcfreqs" );
    EqzCoeffs( i_rate, 1.0f, b_vlcFreqs, &cfg );

    /* Create the static filter config */
    p_sys->i_band = cfg.i_band;
    p_sys->f_alpha = vlc_alloc( p_sys->i_band, sizeof(float) );
    p_sys->f_beta  = vlc_alloc( p_sys->i_band, sizeof(float) );
    p_sys->f_gamma = vlc_alloc( p_sys->i_band, sizeof(float) );
    if( !p_sys->f_alpha || !p_sys->f_beta || !p_sys->f_gamma )
        goto error;

    for( i = 0; i < p_sys->i_band; i++ )
    {
        p_sys->f_alpha[i] = cfg.band[i].f_alpha;
        p_sys->f_beta[i]  = cfg.band[i].f_beta;
        p_sys->f_gamma[i] = cfg.band[i].f_gamma;
    }

    /* Filter dyn config */
    p_sys->b_2eqz = false;
    p_sys->f_gamp = 1.0f;
    p_sys->f_amp  = vlc_alloc( p_sys->i_band, sizeof(float) );
    if( !p_sys->f_amp )
        goto error;

    for( i = 0; i < p_sys->i_band; i++ )
    {
        p_sys->f_amp[i] = 0.0f;
    }

    /* Filter state */
    for( ch = 0; ch < 32; ch++ )
    {
        p_sys->x[ch][0]  =
        p_sys->x[ch][1]  =
        p_sys->x2[ch][0] =
        p_sys->x2[ch][1] = 0.0f;

        for( i = 0; i < p_sys->i_band; i++ )
        {
            p_sys->y[ch][i][0]  =
            p_sys->y[ch][i][1]  =
            p_sys->y2[ch][i][0] =
            p_sys->y2[ch][i][1] = 0.0f;
        }
    }

    var_Create( p_aout, "equalizer-bands", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    var_Create( p_aout, "equalizer-preset", VLC_VAR_STRING | VLC_VAR_DOINHERIT );

    p_sys->b_2eqz = var_CreateGetBool( p_aout, "equalizer-2pass" );

    var_Create( p_aout, "equalizer-preamp", VLC_VAR_FLOAT | VLC_VAR_DOINHERIT );

    /* Get initial values */
    var_Get( p_aout, "equalizer-preset", &val1 );
    var_Get( p_aout, "equalizer-bands", &val2 );
    var_Get( p_aout, "equalizer-preamp", &val3 );

    /* Load the preset only if equalizer-bands is not set. */
    if ( val2.psz_string == NULL || *val2.psz_string == '\0' )
        PresetCallback( VLC_OBJECT( p_aout ), NULL, val1, val1, p_sys );
    free( val1.psz_string );
    BandsCallback(  VLC_OBJECT( p_aout ), NULL, val2, val2, p_sys );
    PreampCallback( VLC_OBJECT( p_aout ), NULL, val3, val3, p_sys );

    /* Exit if we have no preset and no bands value */
    if (!val2.psz_string || !*val2.psz_string)
    {
        msg_Err(p_filter, "No preset selected");
        free( val2.psz_string );
        free( p_sys->f_amp );
        i_ret = VLC_EGENERIC;
        goto error;
    }
    free( val2.psz_string );

    /* Add our own callbacks */
    var_AddCallback( p_aout, "equalizer-preset", PresetCallback, p_sys );
    var_AddCallback( p_aout, "equalizer-bands", BandsCallback, p_sys );
    var_AddCallback( p_aout, "equalizer-preamp", PreampCallback, p_sys );
    var_AddCallback( p_aout, "equalizer-2pass", TwoPassCallback, p_sys );

    msg_Dbg( p_filter, "equalizer loaded for %d Hz with %d bands %d pass",
                        i_rate, p_sys->i_band, p_sys->b_2eqz ? 2 : 1 );
    for( i = 0; i < p_sys->i_band; i++ )
    {
        msg_Dbg( p_filter, "   %.2f Hz -> factor:%f alpha:%f beta:%f gamma:%f",
                 cfg.band[i].f_frequency, p_sys->f_amp[i],
                 p_sys->f_alpha[i], p_sys->f_beta[i], p_sys->f_gamma[i]);
    }
    return VLC_SUCCESS;

error:
    free( p_sys->f_alpha );
    free( p_sys->f_beta );
    free( p_sys->f_gamma );
    return i_ret;
}