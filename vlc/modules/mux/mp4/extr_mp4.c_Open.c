#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  pf_mux; int /*<<< orphan*/  pf_delstream; int /*<<< orphan*/  pf_addstream; int /*<<< orphan*/  pf_control; TYPE_2__* p_sys; scalar_t__ psz_mux; int /*<<< orphan*/  p_cfg; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_7__ {int b_3gp; int b_header_sent; int i_mfhd_sequence; int /*<<< orphan*/  muxh; int /*<<< orphan*/  i_start_dts; scalar_t__ i_written_duration; scalar_t__ i_read_duration; scalar_t__ i_mdat_pos; int /*<<< orphan*/ * pp_streams; scalar_t__ i_nb_streams; scalar_t__ i_pos; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
typedef  enum mp4mux_options { ____Placeholder_mp4mux_options } mp4mux_options ;

/* Variables and functions */
 int /*<<< orphan*/  AddStream ; 
 int /*<<< orphan*/  BRAND_3gp4 ; 
 int /*<<< orphan*/  BRAND_3gp6 ; 
 int /*<<< orphan*/  BRAND_isom ; 
 int /*<<< orphan*/  Control ; 
 int /*<<< orphan*/  DelStream ; 
 int FRAGMENTED ; 
 int /*<<< orphan*/  Mux ; 
 int /*<<< orphan*/  MuxFrag ; 
 int QUICKTIME ; 
 int /*<<< orphan*/  SOUT_CFG_PREFIX ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  config_ChainParse (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  mp4mux_AddExtraBrand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4mux_New (int) ; 
 int /*<<< orphan*/  mp4mux_SetBrand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ppsz_sout_options ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int Open(vlc_object_t *p_this)
{
    sout_mux_t      *p_mux = (sout_mux_t*)p_this;
    sout_mux_sys_t  *p_sys = malloc(sizeof(sout_mux_sys_t));
    if (!p_sys)
        return VLC_ENOMEM;

    msg_Dbg(p_mux, "Mp4 muxer opened");
    config_ChainParse(p_mux, SOUT_CFG_PREFIX, ppsz_sout_options, p_mux->p_cfg);

    enum mp4mux_options options = 0;
    if(p_mux->psz_mux)
    {
        if(!strcmp(p_mux->psz_mux, "mov"))
            options |= QUICKTIME;
        if(!strcmp(p_mux->psz_mux, "mp4frag") || !strcmp(p_mux->psz_mux, "mp4stream"))
            options |= FRAGMENTED;
    }

    p_sys->b_3gp = p_mux->psz_mux && !strcmp(p_mux->psz_mux, "3gp");

    p_sys->muxh = mp4mux_New(options);

    p_sys->i_pos        = 0;
    p_sys->i_nb_streams = 0;
    p_sys->pp_streams   = NULL;
    p_sys->i_mdat_pos   = 0;
    p_sys->b_header_sent = false;

    p_sys->i_read_duration   = 0;
    p_sys->i_written_duration= 0;
    p_sys->i_start_dts = VLC_TICK_INVALID;
    p_sys->i_mfhd_sequence = 1;

    p_mux->p_sys        = p_sys;
    p_mux->pf_control   = Control;
    p_mux->pf_addstream = AddStream;
    p_mux->pf_delstream = DelStream;
    p_mux->pf_mux       = (options & FRAGMENTED) ? MuxFrag : Mux;

    if(p_sys->b_3gp)
    {
        mp4mux_SetBrand(p_sys->muxh, BRAND_3gp6, 0x0);
        mp4mux_AddExtraBrand(p_sys->muxh, BRAND_3gp4);
    }
    else
    {
        mp4mux_SetBrand(p_sys->muxh, BRAND_isom, 0x0);
    }

    return VLC_SUCCESS;
}