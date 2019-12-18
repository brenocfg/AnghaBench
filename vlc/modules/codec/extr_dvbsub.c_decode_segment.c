#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_12__ {int i_id; int i_ancillary_id; } ;
typedef  TYPE_2__ decoder_sys_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
#define  DVBSUB_ST_CLUT_DEFINITION 134 
#define  DVBSUB_ST_DISPLAY_DEFINITION 133 
#define  DVBSUB_ST_ENDOFDISPLAY 132 
#define  DVBSUB_ST_OBJECT_DATA 131 
#define  DVBSUB_ST_PAGE_COMPOSITION 130 
#define  DVBSUB_ST_REGION_COMPOSITION 129 
#define  DVBSUB_ST_STUFFING 128 
 int bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_clut (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_display_definition (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_object (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_page_composition (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_region_composition (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void decode_segment( decoder_t *p_dec, bs_t *s )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    int i_type;
    int i_page_id;
    int i_size;

    /* sync_byte (already checked) */
    //bs_skip( s, 8 );

    /* segment type */
    i_type = bs_read( s, 8 );

    /* page id */
    i_page_id = bs_read( s, 16 );

    /* segment size */
    i_size = bs_read( s, 16 );

    if( ( i_page_id != p_sys->i_id ) &&
        ( i_page_id != p_sys->i_ancillary_id ) )
    {
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "subtitle skipped (page id: %i, %i)",
                 i_page_id, p_sys->i_id );
#endif
        bs_skip( s,  8 * i_size );
        return;
    }

    if( ( p_sys->i_ancillary_id != p_sys->i_id ) &&
        ( i_type == DVBSUB_ST_PAGE_COMPOSITION ) &&
        ( i_page_id == p_sys->i_ancillary_id ) )
    {
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "skipped invalid ancillary subtitle packet" );
#endif
        bs_skip( s,  8 * i_size );
        return;
    }

#ifdef DEBUG_DVBSUB
    if( i_page_id == p_sys->i_id )
        msg_Dbg( p_dec, "segment (id: %i)", i_page_id );
    else
        msg_Dbg( p_dec, "ancillary segment (id: %i)", i_page_id );
#endif

    switch( i_type )
    {
    case DVBSUB_ST_PAGE_COMPOSITION:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "decode_page_composition" );
#endif
        decode_page_composition( p_dec, s, i_size );
        break;

    case DVBSUB_ST_REGION_COMPOSITION:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "decode_region_composition" );
#endif
        decode_region_composition( p_dec, s, i_size );
        break;

    case DVBSUB_ST_CLUT_DEFINITION:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "decode_clut" );
#endif
        decode_clut( p_dec, s, i_size );
        break;

    case DVBSUB_ST_OBJECT_DATA:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "decode_object" );
#endif
        decode_object( p_dec, s, i_size );
        break;

    case DVBSUB_ST_DISPLAY_DEFINITION:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "decode_display_definition" );
#endif
        decode_display_definition( p_dec, s, i_size );
        break;

    case DVBSUB_ST_ENDOFDISPLAY:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "end of display" );
#endif
        bs_skip( s,  8 * i_size );
        break;

    case DVBSUB_ST_STUFFING:
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "skip stuffing" );
#endif
        bs_skip( s,  8 * i_size );
        break;

    default:
        msg_Warn( p_dec, "unsupported segment type: (%04x)", i_type );
        bs_skip( s,  8 * i_size );
        break;
    }
}