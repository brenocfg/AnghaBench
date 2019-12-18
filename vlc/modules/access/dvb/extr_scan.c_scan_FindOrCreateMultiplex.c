#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  scan_tuner_config_t ;
typedef  int /*<<< orphan*/  scan_t ;
typedef  int /*<<< orphan*/  scan_multiplex_t ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_AddMultiplex (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_FindMultiplex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_multiplex_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_multiplex_New (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static scan_multiplex_t *scan_FindOrCreateMultiplex( scan_t *p_scan, uint16_t i_ts_id,
                                                     const scan_tuner_config_t *p_cfg )
{
    scan_multiplex_t *p_mplex = scan_FindMultiplex( p_scan, i_ts_id );
    if( p_mplex == NULL )
    {
        p_mplex = scan_multiplex_New( p_cfg, i_ts_id );
        if( likely(p_mplex) )
        {
            if ( unlikely(!scan_AddMultiplex( p_scan, p_mplex )) ) /* OOM */
            {
                scan_multiplex_Delete( p_mplex );
                return NULL;
            }
        }
    }
    return p_mplex;
}