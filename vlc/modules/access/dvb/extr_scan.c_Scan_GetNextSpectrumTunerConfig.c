#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scan_tuner_config_t ;
struct TYPE_6__ {int type; } ;
struct TYPE_5__ {int /*<<< orphan*/  spectrum; TYPE_2__ parameter; } ;
typedef  TYPE_1__ scan_t ;

/* Variables and functions */
#define  SCAN_DVB_C 129 
#define  SCAN_DVB_T 128 
 int Scan_Next_DVBC (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*) ; 
 int Scan_Next_DVBT (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,double*) ; 
 int VLC_EGENERIC ; 

__attribute__((used)) static int Scan_GetNextSpectrumTunerConfig( scan_t *p_scan, scan_tuner_config_t *p_cfg, double *pf_pos )
{
    int i_ret = VLC_EGENERIC;
    switch( p_scan->parameter.type )
    {
        case SCAN_DVB_T:
            i_ret = Scan_Next_DVBT( &p_scan->parameter, &p_scan->spectrum, p_cfg, pf_pos );
            break;
        case SCAN_DVB_C:
            i_ret = Scan_Next_DVBC( &p_scan->parameter, &p_scan->spectrum, p_cfg, pf_pos );
            break;
        default:
            break;
    }
    return i_ret;
}