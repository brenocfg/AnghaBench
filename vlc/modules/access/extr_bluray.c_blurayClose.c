#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {unsigned int i_title; int i_attachments; int /*<<< orphan*/  psz_bd_path; int /*<<< orphan*/  read_block_lock; TYPE_1__ bdj; int /*<<< orphan*/  pl_info_lock; int /*<<< orphan*/  events_delayed; int /*<<< orphan*/ * attachments; int /*<<< orphan*/ * pp_title; scalar_t__ p_tf_out; int /*<<< orphan*/ * p_out; scalar_t__ p_parser; scalar_t__ bluray; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_RESET (int /*<<< orphan*/ ) ; 
 int MAX_OVERLAY ; 
 int /*<<< orphan*/  TAB_CLEAN (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_close (scalar_t__) ; 
 int /*<<< orphan*/  blurayCloseOverlay (TYPE_2__*,int) ; 
 int /*<<< orphan*/  es_out_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setTitleInfo (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timestamps_filter_es_out_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_demux_chained_Delete (scalar_t__) ; 
 int /*<<< orphan*/  vlc_input_attachment_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_input_title_Delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayClose(vlc_object_t *object)
{
    demux_t *p_demux = (demux_t*)object;
    demux_sys_t *p_sys = p_demux->p_sys;

    setTitleInfo(p_sys, NULL);

    /*
     * Close libbluray first.
     * This will close all the overlays before we release p_vout
     * bd_close(NULL) can crash
     */
    if (p_sys->bluray) {
        bd_close(p_sys->bluray);
    }

    vlc_mutex_lock(&p_sys->bdj.lock);
    for(int i = 0; i < MAX_OVERLAY; i++)
        blurayCloseOverlay(p_demux, i);
    vlc_mutex_unlock(&p_sys->bdj.lock);

    if (p_sys->p_parser)
        vlc_demux_chained_Delete(p_sys->p_parser);

    if (p_sys->p_out != NULL)
        es_out_Delete(p_sys->p_out);
    if(p_sys->p_tf_out)
        timestamps_filter_es_out_Delete(p_sys->p_tf_out);

    /* Titles */
    for (unsigned int i = 0; i < p_sys->i_title; i++)
        vlc_input_title_Delete(p_sys->pp_title[i]);
    TAB_CLEAN(p_sys->i_title, p_sys->pp_title);

    for (int i = 0; i < p_sys->i_attachments; i++)
      vlc_input_attachment_Delete(p_sys->attachments[i]);
    TAB_CLEAN(p_sys->i_attachments, p_sys->attachments);

    ARRAY_RESET(p_sys->events_delayed);

    vlc_mutex_destroy(&p_sys->pl_info_lock);
    vlc_mutex_destroy(&p_sys->bdj.lock);
    vlc_mutex_destroy(&p_sys->read_block_lock);

    free(p_sys->psz_bd_path);
}