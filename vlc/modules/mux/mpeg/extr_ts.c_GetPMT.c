#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_nb_inputs; TYPE_6__** pp_inputs; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ sout_mux_t ;
struct TYPE_18__ {int /*<<< orphan*/  i_pmt_program_number; int /*<<< orphan*/  pmt; int /*<<< orphan*/  i_num_pmt; int /*<<< orphan*/  sdt; TYPE_3__* p_pcr_input; int /*<<< orphan*/  i_pmt_version_number; int /*<<< orphan*/  i_tsid; int /*<<< orphan*/  standard; int /*<<< orphan*/  p_dvbpsi; int /*<<< orphan*/  i_pmtslots; int /*<<< orphan*/  pmtmap; } ;
typedef  TYPE_5__ sout_mux_sys_t ;
struct TYPE_19__ {TYPE_1__* p_fmt; scalar_t__ p_sys; } ;
typedef  TYPE_6__ sout_input_t ;
struct TYPE_15__ {int /*<<< orphan*/  i_pid; } ;
struct TYPE_20__ {TYPE_2__ ts; int /*<<< orphan*/  pes; } ;
typedef  TYPE_7__ sout_input_sys_t ;
typedef  int /*<<< orphan*/  sout_buffer_chain_t ;
struct TYPE_21__ {int /*<<< orphan*/  i_prog; } ;
typedef  TYPE_8__ pmt_map_t ;
struct TYPE_22__ {TYPE_2__* ts; int /*<<< orphan*/ * pes; TYPE_1__* fmt; int /*<<< orphan*/  i_mapped_prog; } ;
typedef  TYPE_9__ pes_mapped_stream_t ;
struct TYPE_16__ {scalar_t__ p_sys; } ;
struct TYPE_14__ {int i_id; } ;
typedef  int /*<<< orphan*/  PEStoTSCallback ;

/* Variables and functions */
 scalar_t__ BufferChainAppend ; 
 int /*<<< orphan*/  BuildPMT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_9__*) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_4__*) ; 
 TYPE_8__* bsearch (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intcompare ; 

__attribute__((used)) static void GetPMT( sout_mux_t *p_mux, sout_buffer_chain_t *c )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    pes_mapped_stream_t mappeds[p_mux->i_nb_inputs];

    for (int i_stream = 0; i_stream < p_mux->i_nb_inputs; i_stream++ )
    {
        sout_input_t *p_input = p_mux->pp_inputs[i_stream];
        sout_input_sys_t *p_stream = (sout_input_sys_t*)p_input->p_sys;

        int i_pidinput = p_input->p_fmt->i_id;
        pmt_map_t *p_usepid = bsearch( &i_pidinput, p_sys->pmtmap,
                                       p_sys->i_pmtslots, sizeof(pmt_map_t), intcompare );

        /* If there's an error somewhere, dump it to the first pmt */
        mappeds[i_stream].i_mapped_prog = p_usepid ? p_usepid->i_prog : 0;
        mappeds[i_stream].fmt = p_input->p_fmt;
        mappeds[i_stream].pes = &p_stream->pes;
        mappeds[i_stream].ts = &p_stream->ts;
    }

    BuildPMT( p_sys->p_dvbpsi, VLC_OBJECT(p_mux), p_sys->standard,
              c, (PEStoTSCallback)BufferChainAppend,
              p_sys->i_tsid, p_sys->i_pmt_version_number,
              ((sout_input_sys_t *)p_sys->p_pcr_input->p_sys)->ts.i_pid,
              &p_sys->sdt,
              p_sys->i_num_pmt, p_sys->pmt, p_sys->i_pmt_program_number,
              p_mux->i_nb_inputs, mappeds );
}