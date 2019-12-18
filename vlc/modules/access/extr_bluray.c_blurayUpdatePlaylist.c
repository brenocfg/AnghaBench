#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_8__ {size_t cur_title; int updates; scalar_t__ b_menu; int /*<<< orphan*/ * pp_title; int /*<<< orphan*/  bluray; scalar_t__ cur_seekpoint; } ;
typedef  TYPE_2__ demux_sys_t ;
typedef  int /*<<< orphan*/  BLURAY_TITLE_INFO ;

/* Variables and functions */
 int INPUT_UPDATE_SEEKPOINT ; 
 int INPUT_UPDATE_TITLE ; 
 int INPUT_UPDATE_TITLE_LIST ; 
 size_t bd_get_current_title (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bd_get_playlist_info (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blurayResetStillImage (TYPE_1__*) ; 
 int /*<<< orphan*/  blurayRestartParser (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  blurayUpdateTitleInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setTitleInfo (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void blurayUpdatePlaylist(demux_t *p_demux, unsigned i_playlist)
{
    demux_sys_t *p_sys = p_demux->p_sys;

    blurayRestartParser(p_demux, true, false);

    /* read title info and init some values */
    if (!p_sys->b_menu)
        p_sys->cur_title = bd_get_current_title(p_sys->bluray);
    p_sys->cur_seekpoint = 0;
    p_sys->updates |= INPUT_UPDATE_TITLE | INPUT_UPDATE_SEEKPOINT;

    BLURAY_TITLE_INFO *p_title_info = bd_get_playlist_info(p_sys->bluray, i_playlist, 0);
    if (p_title_info) {
        blurayUpdateTitleInfo(p_sys->pp_title[p_sys->cur_title], p_title_info);
        if (p_sys->b_menu)
            p_sys->updates |= INPUT_UPDATE_TITLE_LIST;
    }
    setTitleInfo(p_sys, p_title_info);

    blurayResetStillImage(p_demux);
}