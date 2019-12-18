#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  scan_tuner_config_t ;
struct TYPE_5__ {int i_snr; int b_scanned; void* i_sdt_version; void* i_nit_version; int /*<<< orphan*/ * pp_services; scalar_t__ i_services; int /*<<< orphan*/ * psz_network_name; int /*<<< orphan*/  i_network_id; int /*<<< orphan*/  i_ts_id; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_1__ scan_multiplex_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_ID_RESERVED ; 
 void* UINT8_MAX ; 
 scalar_t__ likely (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static scan_multiplex_t *scan_multiplex_New( const scan_tuner_config_t *p_cfg, uint16_t i_ts_id )
{
    scan_multiplex_t *p_mplex = malloc( sizeof(*p_mplex) );
    if( likely(p_mplex) )
    {
        p_mplex->cfg = *p_cfg;
        p_mplex->i_ts_id = i_ts_id;
        p_mplex->i_network_id = NETWORK_ID_RESERVED;
        p_mplex->psz_network_name = NULL;
        p_mplex->i_services = 0;
        p_mplex->pp_services = NULL;
        p_mplex->i_nit_version = UINT8_MAX;
        p_mplex->i_sdt_version = UINT8_MAX;
        p_mplex->i_snr = -1;
        p_mplex->b_scanned = false;
    }
    return p_mplex;
}