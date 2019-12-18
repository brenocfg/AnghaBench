#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {TYPE_7__* cell_playback; } ;
typedef  TYPE_10__ pgc_t ;
struct TYPE_20__ {TYPE_9__* vts_vobu_admap; TYPE_8__* vts_c_adt; TYPE_6__* vts_pgcit; TYPE_3__* vts_ptt_srpt; } ;
typedef  TYPE_11__ ifo_handle_t ;
struct TYPE_21__ {TYPE_13__* p_sys; } ;
typedef  TYPE_12__ demux_t ;
struct TYPE_22__ {int i_title_start_cell; int i_title_end_cell; int i_title_offset; int i_chapters; int i_ttn; int cur_chapter; int i_cur_block; int i_next_vobu; int i_pack_len; int i_cur_cell; int i_chapter; TYPE_10__* p_cur_pgc; int /*<<< orphan*/  updates; TYPE_11__* p_vts_file; } ;
typedef  TYPE_13__ demux_sys_t ;
struct TYPE_23__ {scalar_t__ const start_sector; } ;
typedef  TYPE_14__ cell_adr_t ;
struct TYPE_32__ {int last_byte; scalar_t__* vobu_start_sectors; } ;
struct TYPE_31__ {int nr_of_vobs; TYPE_14__* cell_adr_table; } ;
struct TYPE_30__ {scalar_t__ first_sector; scalar_t__ last_sector; } ;
struct TYPE_29__ {TYPE_5__* pgci_srp; } ;
struct TYPE_28__ {TYPE_4__* pgc; } ;
struct TYPE_27__ {int* program_map; } ;
struct TYPE_26__ {TYPE_2__* title; } ;
struct TYPE_25__ {TYPE_1__* ptt; } ;
struct TYPE_24__ {int pgcn; int pgn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DvdReadFindCell (TYPE_12__*) ; 
 int /*<<< orphan*/  INPUT_UPDATE_SEEKPOINT ; 
 int VOBU_ADMAP_SIZE ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_12__*,char*,int,int,int,int,scalar_t__,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  msg_Err (TYPE_12__*,char*,int) ; 

__attribute__((used)) static void DvdReadSeek( demux_t *p_demux, int i_block_offset )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_chapter = 0;
    int i_cell = 0;
    int i_block;
    const pgc_t *p_pgc = p_sys->p_cur_pgc;
    const ifo_handle_t *p_vts = p_sys->p_vts_file;

    /* Find cell */
    i_block = i_block_offset;
    for( i_cell = p_sys->i_title_start_cell;
         i_cell <= p_sys->i_title_end_cell; i_cell++ )
    {
        if( i_block < (int)p_pgc->cell_playback[i_cell].last_sector -
            (int)p_pgc->cell_playback[i_cell].first_sector + 1 ) break;

        i_block -= (p_pgc->cell_playback[i_cell].last_sector -
            p_pgc->cell_playback[i_cell].first_sector + 1);
    }
    if( i_cell > p_sys->i_title_end_cell )
    {
        msg_Err( p_demux, "couldn't find cell for block %i", i_block_offset );
        return;
    }
    i_block += p_pgc->cell_playback[i_cell].first_sector;
    p_sys->i_title_offset = i_block_offset;

    /* Find chapter */
    for( i_chapter = 0; i_chapter < p_sys->i_chapters; i_chapter++ )
    {
        int pgc_id, pgn, i_tmp;

        pgc_id = p_vts->vts_ptt_srpt->title[
                    p_sys->i_ttn - 1].ptt[i_chapter].pgcn;
        pgn = p_vts->vts_ptt_srpt->title[
                    p_sys->i_ttn - 1].ptt[i_chapter].pgn;

        i_tmp = p_vts->vts_pgcit->pgci_srp[pgc_id - 1].pgc->program_map[pgn-1];

        if( i_tmp > i_cell ) break;
    }

    if( i_chapter < p_sys->i_chapters &&
        p_sys->cur_chapter != i_chapter )
    {
        p_sys->updates |= INPUT_UPDATE_SEEKPOINT;
        p_sys->cur_chapter = i_chapter;
    }

    /* Find vobu */
    /* see ifo_read.c / ifoRead_VOBU_ADMAP_internal for index count */
    int i_vobu = 1;
    const size_t i_vobu_sect_index_count =
            (p_vts->vts_vobu_admap->last_byte + 1 - VOBU_ADMAP_SIZE) / sizeof(uint32_t);
    for( size_t i=0; i<i_vobu_sect_index_count; i++ )
    {
        if( p_vts->vts_vobu_admap->vobu_start_sectors[i] > (uint32_t) i_block )
            break;
        i_vobu = i + 1;
    }

#if 1
    int i_sub_cell = 1;
    /* Find sub_cell */
    /* need to check cell # <= vob count as cell table alloc only ensures:
     * info_length / sizeof(cell_adr_t) < c_adt->nr_of_vobs, see ifo_read.c */
    const uint32_t vobu_start_sector = p_vts->vts_vobu_admap->vobu_start_sectors[i_vobu-1];
    for( int i = 0; i + 1<p_vts->vts_c_adt->nr_of_vobs; i++ )
    {
        const cell_adr_t *p_cell = &p_vts->vts_c_adt->cell_adr_table[i];
        if(p_cell->start_sector <= vobu_start_sector)
           i_sub_cell = i + 1;
    }

    msg_Dbg( p_demux, "cell %d i_sub_cell %d chapter %d vobu %d "
             "cell_sector %d vobu_sector %d sub_cell_sector %d",
             i_cell, i_sub_cell, i_chapter, i_vobu,
             p_sys->p_cur_pgc->cell_playback[i_cell].first_sector,
             p_vts->vts_vobu_admap->vobu_start_sectors[i_vobu],
             p_vts->vts_c_adt->cell_adr_table[i_sub_cell - 1].start_sector);
#endif

    p_sys->i_cur_block = i_block;
    if(likely( (size_t)i_vobu < i_vobu_sect_index_count ))
        p_sys->i_next_vobu = p_vts->vts_vobu_admap->vobu_start_sectors[i_vobu];
    else
        p_sys->i_next_vobu = i_block;
    p_sys->i_pack_len = p_sys->i_next_vobu - i_block;
    p_sys->i_cur_cell = i_cell;
    p_sys->i_chapter = i_chapter;
    DvdReadFindCell( p_demux );

    return;
}