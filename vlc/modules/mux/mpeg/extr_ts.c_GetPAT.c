#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_pmt_program_number; int /*<<< orphan*/  pmt; int /*<<< orphan*/  i_num_pmt; int /*<<< orphan*/  pat; int /*<<< orphan*/  i_pat_version_number; int /*<<< orphan*/  i_tsid; int /*<<< orphan*/  p_dvbpsi; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
typedef  int /*<<< orphan*/  sout_buffer_chain_t ;
typedef  int /*<<< orphan*/  PEStoTSCallback ;

/* Variables and functions */
 scalar_t__ BufferChainAppend ; 
 int /*<<< orphan*/  BuildPAT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GetPAT( sout_mux_t *p_mux, sout_buffer_chain_t *c )
{
    sout_mux_sys_t       *p_sys = p_mux->p_sys;

    BuildPAT( p_sys->p_dvbpsi,
              c, (PEStoTSCallback)BufferChainAppend,
              p_sys->i_tsid, p_sys->i_pat_version_number,
              &p_sys->pat,
              p_sys->i_num_pmt, p_sys->pmt, p_sys->i_pmt_program_number );
}