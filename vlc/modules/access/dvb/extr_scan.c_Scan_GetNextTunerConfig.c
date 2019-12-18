#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int i_bandwidth; int i_symbolrate; int /*<<< orphan*/  type; int /*<<< orphan*/  inner_fec; int /*<<< orphan*/  polarization; int /*<<< orphan*/  coderate_lp; int /*<<< orphan*/  coderate_hp; int /*<<< orphan*/  modulation; int /*<<< orphan*/  i_frequency; } ;
typedef  TYPE_3__ scan_tuner_config_t ;
struct TYPE_13__ {scalar_t__ b_use_nit; } ;
struct TYPE_12__ {int /*<<< orphan*/  i_index; } ;
struct TYPE_15__ {double i_scanlist; double i_multiplex; int i_multiplex_toscan; TYPE_7__** pp_multiplex; int /*<<< orphan*/  b_multiplexes_from_nit; TYPE_2__ parameter; int /*<<< orphan*/ * p_scanlist; TYPE_1__ spectrum; TYPE_5__* p_current; } ;
typedef  TYPE_4__ scan_t ;
struct TYPE_16__ {int i_bw; int delivery; int i_rate; struct TYPE_16__* p_next; int /*<<< orphan*/  inner_fec; int /*<<< orphan*/  polarization; int /*<<< orphan*/  coderate_lp; int /*<<< orphan*/  coderate_hp; int /*<<< orphan*/  modulation; int /*<<< orphan*/  i_freq; } ;
typedef  TYPE_5__ scan_list_entry_t ;
struct TYPE_17__ {TYPE_3__ cfg; int /*<<< orphan*/  b_scanned; } ;

/* Variables and functions */
#define  SCAN_DELIVERY_DVB_C 131 
#define  SCAN_DELIVERY_DVB_S 130 
#define  SCAN_DELIVERY_DVB_T 129 
#define  SCAN_DELIVERY_UNKNOWN 128 
 int /*<<< orphan*/  SCAN_DVB_C ; 
 int /*<<< orphan*/  SCAN_DVB_S ; 
 int /*<<< orphan*/  SCAN_DVB_T ; 
 int /*<<< orphan*/  SCAN_NONE ; 
 int Scan_GetNextSpectrumTunerConfig (TYPE_4__*,TYPE_3__*,double*) ; 
 int VLC_ENOITEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  scan_SetMultiplexScanStatus (TYPE_4__*,TYPE_7__*,int) ; 

__attribute__((used)) static int Scan_GetNextTunerConfig( scan_t *p_scan, scan_tuner_config_t *p_cfg, double *pf_pos )
{
    /* Note: Do not forget to advance current scan (avoid frontend tuning errors loops ) */
    if( p_scan->p_scanlist && p_scan->p_current )
    {
        const scan_list_entry_t *p_entry = p_scan->p_current;
        p_cfg->i_frequency = p_entry->i_freq;
        p_cfg->i_bandwidth = p_entry->i_bw / 1000000;
        p_cfg->modulation = p_entry->modulation;

        switch( p_entry->delivery )
        {
            case SCAN_DELIVERY_UNKNOWN:
                break;
            case SCAN_DELIVERY_DVB_T:
                p_cfg->coderate_hp = p_entry->coderate_hp;
                p_cfg->coderate_lp = p_entry->coderate_lp;
                p_cfg->type = SCAN_DVB_T;
                break;
            case SCAN_DELIVERY_DVB_S:
                p_cfg->type = SCAN_DVB_S;
                p_cfg->polarization = p_entry->polarization;
                p_cfg->i_symbolrate = p_entry->i_rate / 1000;
                p_cfg->inner_fec = p_entry->inner_fec;
                break;
            case SCAN_DELIVERY_DVB_C:
                p_cfg->type = SCAN_DVB_C;
                p_cfg->i_symbolrate = p_entry->i_rate / 1000;
                p_cfg->inner_fec = p_entry->inner_fec;
                break;
            default:
                p_cfg->type = SCAN_NONE;
                break;
        }

        p_scan->p_current = p_scan->p_current->p_next;
        *pf_pos = (double) p_scan->spectrum.i_index++ / p_scan->i_scanlist;

        return VLC_SUCCESS;
    }

    if( p_scan->p_scanlist == NULL &&
        ( p_scan->i_multiplex == 0 || /* Stop frequency scanning if we've found a valid NIT */
         (p_scan->parameter.b_use_nit && !p_scan->b_multiplexes_from_nit) ) )
    {
        int i_ret = Scan_GetNextSpectrumTunerConfig( p_scan, p_cfg, pf_pos );
        if( i_ret == VLC_SUCCESS )
            return i_ret;
    }

    if( p_scan->i_multiplex_toscan )
    {
        for( size_t i=0; i<p_scan->i_multiplex_toscan; i++ )
        {
            if( !p_scan->pp_multiplex[i]->b_scanned )
            {
                scan_SetMultiplexScanStatus( p_scan, p_scan->pp_multiplex[i], true );
                *p_cfg = p_scan->pp_multiplex[i]->cfg;
                *pf_pos = (double) 1.0 - (p_scan->i_multiplex / p_scan->i_multiplex_toscan);
                return VLC_SUCCESS;
            }
        }
    }

    return VLC_ENOITEM;
}