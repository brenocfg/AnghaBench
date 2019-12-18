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
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_out; scalar_t__ p_parser; int /*<<< orphan*/  p_tf_out; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_DISABLE_OUTPUT ; 
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_ENABLE_OUTPUT ; 
 int /*<<< orphan*/  BLURAY_ES_OUT_CONTROL_RANDOM_ACCESS ; 
 int /*<<< orphan*/  ES_OUT_TF_FILTER_RESET ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  es_out_Control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_demux_chained_Delete (scalar_t__) ; 
 scalar_t__ vlc_demux_chained_New (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blurayRestartParser(demux_t *p_demux, bool b_flush, bool b_random_access)
{
    /*
     * This is a hack and will have to be removed.
     * The parser should be flushed, and not destroy/created each time
     * we are changing title.
     */
    demux_sys_t *p_sys = p_demux->p_sys;

    if(b_flush)
        es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_DISABLE_OUTPUT);

    if (p_sys->p_parser)
        vlc_demux_chained_Delete(p_sys->p_parser);

    if(b_flush)
        es_out_Control(p_sys->p_tf_out, ES_OUT_TF_FILTER_RESET);

    p_sys->p_parser = vlc_demux_chained_New(VLC_OBJECT(p_demux), "ts", p_sys->p_out);
    if (!p_sys->p_parser)
        msg_Err(p_demux, "Failed to create TS demuxer");

    es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_ENABLE_OUTPUT);

    es_out_Control(p_sys->p_out, BLURAY_ES_OUT_CONTROL_RANDOM_ACCESS, b_random_access);
}