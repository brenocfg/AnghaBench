#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_step; int /*<<< orphan*/  i_max; int /*<<< orphan*/  i_min; } ;
struct TYPE_10__ {int b_exhaustive; int b_modulation_set; int /*<<< orphan*/  i_symbolrate; TYPE_1__ frequency; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ scan_parameter_t ;
struct TYPE_9__ {int caps; int /*<<< orphan*/  frequency_stepsize; int /*<<< orphan*/  frequency_max; int /*<<< orphan*/  frequency_min; } ;
struct TYPE_11__ {TYPE_2__ info; } ;
typedef  TYPE_4__ frontend_t ;
struct TYPE_12__ {TYPE_4__* p_frontend; } ;
typedef  TYPE_5__ dvb_sys_t ;

/* Variables and functions */
 int FE_CAN_QAM_AUTO ; 
 int /*<<< orphan*/  SCAN_DVB_C ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  var_GetInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ScanParametersDvbC( vlc_object_t *p_access, dvb_sys_t *p_sys, scan_parameter_t *p_scan )
{
    const frontend_t *p_frontend = p_sys->p_frontend;

    p_scan->type = SCAN_DVB_C;
    p_scan->b_exhaustive = false;

    /* */
    p_scan->frequency.i_min = p_frontend->info.frequency_min;
    p_scan->frequency.i_max = p_frontend->info.frequency_max;
    p_scan->frequency.i_step = p_frontend->info.frequency_stepsize;

    /* if frontend can do auto, don't scan them */
    p_scan->b_modulation_set = ( p_frontend->info.caps & FE_CAN_QAM_AUTO );
    /* our scanning code flips modulation from 16..256 automaticly*/

    /* if user supplies symbolrate, don't scan those */
    p_scan->i_symbolrate = var_GetInteger( p_access, "dvb-srate" );

    return VLC_SUCCESS;
}