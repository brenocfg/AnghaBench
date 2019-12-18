#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int* program_map; } ;
typedef  TYPE_8__ pgc_t ;
struct TYPE_23__ {TYPE_10__* p_sys; } ;
typedef  TYPE_9__ demux_t ;
struct TYPE_13__ {size_t i_cur_cell; int i_angle; int i_next_cell; int i_chapter; int i_chapters; int i_ttn; int cur_chapter; int /*<<< orphan*/  updates; TYPE_7__* p_vts_file; TYPE_1__* p_cur_pgc; } ;
typedef  TYPE_10__ demux_sys_t ;
struct TYPE_14__ {scalar_t__ block_type; scalar_t__ block_mode; } ;
typedef  TYPE_11__ cell_playback_t ;
struct TYPE_21__ {TYPE_6__* vts_pgcit; TYPE_4__* vts_ptt_srpt; } ;
struct TYPE_20__ {TYPE_5__* pgci_srp; } ;
struct TYPE_19__ {TYPE_8__* pgc; } ;
struct TYPE_18__ {TYPE_3__* title; } ;
struct TYPE_17__ {TYPE_2__* ptt; } ;
struct TYPE_16__ {int pgcn; int pgn; } ;
struct TYPE_15__ {TYPE_11__* cell_playback; } ;

/* Variables and functions */
 scalar_t__ BLOCK_MODE_LAST_CELL ; 
 scalar_t__ BLOCK_TYPE_ANGLE_BLOCK ; 
 int /*<<< orphan*/  INPUT_UPDATE_SEEKPOINT ; 

__attribute__((used)) static void DvdReadFindCell( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    const pgc_t *p_pgc;
    int   pgc_id, pgn;
    int   i = 0;

    const cell_playback_t *cell = p_sys->p_cur_pgc->cell_playback;
    if( cell[p_sys->i_cur_cell].block_type == BLOCK_TYPE_ANGLE_BLOCK )
    {
        p_sys->i_cur_cell += p_sys->i_angle - 1;

        while( cell[p_sys->i_cur_cell+i].block_mode != BLOCK_MODE_LAST_CELL )
        {
            i++;
        }
        p_sys->i_next_cell = p_sys->i_cur_cell + i + 1;
    }
    else
    {
        p_sys->i_next_cell = p_sys->i_cur_cell + 1;
    }

    if( p_sys->i_chapter + 1 >= p_sys->i_chapters ) return;

    pgc_id = p_sys->p_vts_file->vts_ptt_srpt->title[
                p_sys->i_ttn - 1].ptt[p_sys->i_chapter + 1].pgcn;
    pgn = p_sys->p_vts_file->vts_ptt_srpt->title[
              p_sys->i_ttn - 1].ptt[p_sys->i_chapter + 1].pgn;
    p_pgc = p_sys->p_vts_file->vts_pgcit->pgci_srp[pgc_id - 1].pgc;

    if( p_sys->i_cur_cell >= p_pgc->program_map[pgn - 1] - 1 )
    {
        p_sys->i_chapter++;

        if( p_sys->i_chapter < p_sys->i_chapters &&
            p_sys->cur_chapter != p_sys->i_chapter )
        {
            p_sys->updates |= INPUT_UPDATE_SEEKPOINT;
            p_sys->cur_chapter = p_sys->i_chapter;
        }
    }
}