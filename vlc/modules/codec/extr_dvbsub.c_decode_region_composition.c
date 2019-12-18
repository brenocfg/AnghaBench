#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_13__ {int i_id; int i_version; int i_object_defs; int i_width; int i_height; int i_depth; int i_level_comp; int i_clut; TYPE_2__* p_object_defs; TYPE_2__* p_pixbuf; struct TYPE_13__* p_next; } ;
typedef  TYPE_1__ dvbsub_region_t ;
struct TYPE_14__ {void* i_bg_pc; void* i_fg_pc; void* i_type; struct TYPE_14__* psz_text; void* i_y; void* i_x; void* i_id; } ;
typedef  TYPE_2__ dvbsub_objectdef_t ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_16__ {TYPE_1__* p_regions; } ;
typedef  TYPE_4__ decoder_sys_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 void* DVBSUB_OT_BASIC_CHAR ; 
 void* DVBSUB_OT_COMPOSITE_STRING ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,...) ; 
 TYPE_2__* xmalloc (int) ; 
 TYPE_2__* xrealloc (TYPE_2__*,int) ; 

__attribute__((used)) static void decode_region_composition( decoder_t *p_dec, bs_t *s, uint16_t i_segment_length )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    dvbsub_region_t *p_region, **pp_region = &p_sys->p_regions;
    int i_processed_length, i_id, i_version;
    int i_width, i_height, i_level_comp, i_depth, i_clut;
    int i_8_bg, i_4_bg, i_2_bg;
    bool b_fill;

    i_id = bs_read( s, 8 );
    i_version = bs_read( s, 4 );

    /* Check if we already have this region */
    for( p_region = p_sys->p_regions; p_region != NULL;
         p_region = p_region->p_next )
    {
        pp_region = &p_region->p_next;
        if( p_region->i_id == i_id ) break;
    }

    /* Check version number */
    if( p_region && ( p_region->i_version == i_version ) )
    {
        bs_skip( s, 8 * (i_segment_length - 1) - 4 );
        return;
    }

    if( !p_region )
    {
#ifdef DEBUG_DVBSUB
        msg_Dbg( p_dec, "new region: %i", i_id );
#endif
        p_region = *pp_region = calloc( 1, sizeof(dvbsub_region_t) );
        if( !p_region )
            return;
        p_region->p_object_defs = NULL;
        p_region->p_pixbuf = NULL;
        p_region->p_next = NULL;
    }

    /* Region attributes */
    p_region->i_id = i_id;
    p_region->i_version = i_version;
    b_fill = bs_read( s, 1 );
    bs_skip( s, 3 ); /* Reserved */

    i_width = bs_read( s, 16 );
    i_height = bs_read( s, 16 );
#ifdef DEBUG_DVBSUB
    msg_Dbg( p_dec, " width=%d height=%d", i_width, i_height );
#endif
    i_level_comp = bs_read( s, 3 );
    i_depth = bs_read( s, 3 );
    bs_skip( s, 2 ); /* Reserved */
    i_clut = bs_read( s, 8 );

    i_8_bg = bs_read( s, 8 );
    i_4_bg = bs_read( s, 4 );
    i_2_bg = bs_read( s, 2 );
    bs_skip( s, 2 ); /* Reserved */

    /* Free old object defs */
    while( p_region->i_object_defs )
        free( p_region->p_object_defs[--p_region->i_object_defs].psz_text );

    free( p_region->p_object_defs );
    p_region->p_object_defs = NULL;

    /* Extra sanity checks */
    if( ( p_region->i_width != i_width ) ||
        ( p_region->i_height != i_height ) )
    {
        if( p_region->p_pixbuf )
        {
            msg_Dbg( p_dec, "region size changed (%dx%d->%dx%d)",
                     p_region->i_width, p_region->i_height, i_width, i_height );
            free( p_region->p_pixbuf );
        }

        p_region->p_pixbuf = xmalloc( i_height * i_width );
        p_region->i_depth = 0;
        b_fill = true;
    }
    if( p_region->i_depth &&
        ( ( p_region->i_depth != i_depth ) ||
          ( p_region->i_level_comp != i_level_comp ) ||
          ( p_region->i_clut != i_clut) ) )
    {
        msg_Dbg( p_dec, "region parameters changed (not allowed)" );
    }

    /* Erase background of region */
    if( b_fill )
    {
        int i_background = ( i_depth == 1 ) ? i_2_bg :
            ( ( i_depth == 2 ) ? i_4_bg : i_8_bg );
        memset( p_region->p_pixbuf, i_background, i_width * i_height );
    }

    p_region->i_width = i_width;
    p_region->i_height = i_height;
    p_region->i_level_comp = i_level_comp;
    p_region->i_depth = i_depth;
    p_region->i_clut = i_clut;

    /* List of objects in the region */
    i_processed_length = 10;
    while( i_processed_length < i_segment_length )
    {
        dvbsub_objectdef_t *p_obj;

        /* We create a new object */
        p_region->i_object_defs++;
        p_region->p_object_defs = xrealloc( p_region->p_object_defs,
                     sizeof(dvbsub_objectdef_t) * p_region->i_object_defs );

        /* We parse object properties */
        p_obj = &p_region->p_object_defs[p_region->i_object_defs - 1];
        p_obj->i_id         = bs_read( s, 16 );
        p_obj->i_type       = bs_read( s, 2 );
        bs_skip( s, 2 ); /* Provider */
        p_obj->i_x          = bs_read( s, 12 );
        bs_skip( s, 4 ); /* Reserved */
        p_obj->i_y          = bs_read( s, 12 );
        p_obj->psz_text     = NULL;

        i_processed_length += 6;

        if( ( p_obj->i_type == DVBSUB_OT_BASIC_CHAR ) ||
            ( p_obj->i_type == DVBSUB_OT_COMPOSITE_STRING ) )
        {
            p_obj->i_fg_pc =  bs_read( s, 8 );
            p_obj->i_bg_pc =  bs_read( s, 8 );
            i_processed_length += 2;
        }
    }
}