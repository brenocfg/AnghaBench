#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
struct TYPE_10__ {scalar_t__ i_frequency; } ;
typedef  TYPE_1__ scan_tuner_config_t ;
struct TYPE_11__ {double i_time_start; int /*<<< orphan*/ * p_dialog_id; int /*<<< orphan*/  p_obj; int /*<<< orphan*/  parameter; } ;
typedef  TYPE_2__ scan_t ;

/* Variables and functions */
 int MSTRTIME_MAX_SIZE ; 
 int Scan_GetNextTunerConfig (TYPE_2__*,TYPE_1__*,double*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,double) ; 
 size_t scan_CountServices (TYPE_2__*) ; 
 scalar_t__ scan_IsCancelled (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_tuner_config_Init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secstotimestr (char*,int const) ; 
 int /*<<< orphan*/ * vlc_dialog_display_progress (int /*<<< orphan*/ ,int,double,char*,char*,char const*,double,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_dialog_update_progress_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double,char const*,double,size_t const,int /*<<< orphan*/ ) ; 
 double vlc_tick_now () ; 

__attribute__((used)) static int scan_Next( scan_t *p_scan, scan_tuner_config_t *p_cfg )
{
    double f_position;
    int i_ret;

    if( scan_IsCancelled( p_scan ) )
        return VLC_EGENERIC;

    //do
    {
        scan_tuner_config_Init( p_cfg, &p_scan->parameter );

        i_ret = Scan_GetNextTunerConfig( p_scan, p_cfg, &f_position );
        if( i_ret )
            return i_ret;
    }
    //while( !scan_tuner_config_ParametersValidate( &p_scan->parameter, p_cfg ) );

    const size_t i_total_services = scan_CountServices( p_scan );
    const vlc_tick_t i_eta = f_position > 0.005 ? (vlc_tick_now() - p_scan->i_time_start) * ( 1.0 / f_position - 1.0 ) : -1;
    char psz_eta[MSTRTIME_MAX_SIZE];
    const char *psz_fmt = _("%.1f MHz (%d services)\n~%s remaining");

    if( i_eta >= 0 )
        msg_Info( p_scan->p_obj, "Scan ETA %s | %f", secstotimestr( psz_eta, i_eta/1000000 ), f_position * 100 );

    if( p_scan->p_dialog_id == NULL )
    {
        p_scan->p_dialog_id =
            vlc_dialog_display_progress( p_scan->p_obj, false,
                                         f_position, _("Cancel"),
                                         _("Scanning DVB"), psz_fmt,
                                         (double)p_cfg->i_frequency / 1000000,
                                         i_total_services,
                                         secstotimestr( psz_eta, i_eta/1000000 ) );
    }
    else
    {
        vlc_dialog_update_progress_text( p_scan->p_obj, p_scan->p_dialog_id,
                                         f_position, psz_fmt,
                                         (double)p_cfg->i_frequency / 1000000,
                                         i_total_services,
                                         secstotimestr( psz_eta, i_eta/1000000 ) );
    }

    return VLC_SUCCESS;
}