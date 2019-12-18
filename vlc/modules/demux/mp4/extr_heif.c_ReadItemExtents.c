#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct heif_private_t {int /*<<< orphan*/  p_root; } ;
struct TYPE_26__ {int /*<<< orphan*/  s; scalar_t__ p_sys; } ;
typedef  TYPE_6__ demux_t ;
struct TYPE_27__ {struct TYPE_27__* p_next; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_7__ block_t ;
struct TYPE_22__ {TYPE_1__* p_binary; } ;
struct TYPE_28__ {scalar_t__ i_type; struct TYPE_28__ const* p_next; struct TYPE_28__ const* p_first; scalar_t__ i_pos; TYPE_2__ data; } ;
struct TYPE_25__ {size_t i_to_item_id; } ;
struct TYPE_24__ {size_t i_item_id; size_t i_extent_count; int i_construction_method; TYPE_3__* p_extents; scalar_t__ i_base_offset; } ;
struct TYPE_23__ {size_t i_extent_index; scalar_t__ i_extent_length; scalar_t__ i_extent_offset; } ;
struct TYPE_21__ {int /*<<< orphan*/  i_blob; int /*<<< orphan*/  p_blob; } ;
struct TYPE_20__ {size_t i_item_count; size_t i_from_item_id; size_t i_reference_count; TYPE_5__* p_references; TYPE_4__* p_items; } ;
typedef  TYPE_8__ const MP4_Box_t ;

/* Variables and functions */
 TYPE_18__* BOXDATA (TYPE_8__ const*) ; 
 TYPE_8__ const* MP4_BoxGet (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 
 scalar_t__ VLC_SUCCESS ; 
 TYPE_7__* block_Alloc (int /*<<< orphan*/ ) ; 
 TYPE_7__* block_ChainGather (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp4_box_headersize (TYPE_8__ const*) ; 
 TYPE_7__* vlc_stream_Block (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vlc_stream_Seek (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static block_t *ReadItemExtents( demux_t *p_demux, uint32_t i_item_id,
                                 const MP4_Box_t *p_shared_header )
{
    struct heif_private_t *p_sys = (void *) p_demux->p_sys;
    block_t *p_block = NULL;

    MP4_Box_t *p_iloc = MP4_BoxGet( p_sys->p_root, "meta/iloc" );
    if( !p_iloc )
        return p_block;

    for( uint32_t i=0; i<BOXDATA(p_iloc)->i_item_count; i++ )
    {
        if( BOXDATA(p_iloc)->p_items[i].i_item_id != i_item_id )
            continue;

        block_t **pp_append = &p_block;

        /* Shared prefix data, ex: JPEG */
        if( p_shared_header )
        {
            *pp_append = block_Alloc( p_shared_header->data.p_binary->i_blob );
            if( *pp_append )
            {
                memcpy( (*pp_append)->p_buffer,
                        p_shared_header->data.p_binary->p_blob,
                        p_shared_header->data.p_binary->i_blob );
                pp_append = &((*pp_append)->p_next);
            }
        }

        for( uint16_t j=0; j<BOXDATA(p_iloc)->p_items[i].i_extent_count; j++ )
        {
            uint64_t i_offset = BOXDATA(p_iloc)->p_items[i].i_base_offset +
                                BOXDATA(p_iloc)->p_items[i].p_extents[j].i_extent_offset;
            uint64_t i_length = BOXDATA(p_iloc)->p_items[i].p_extents[j].i_extent_length;

            if( BOXDATA(p_iloc)->p_items[i].i_construction_method < 2 )
            {
                /* Extents are in 1:file, 2:idat */
                if( BOXDATA(p_iloc)->p_items[i].i_construction_method == 1 )
                {
                    MP4_Box_t *idat = MP4_BoxGet( p_sys->p_root, "meta/idat" );
                    if(!idat)
                        break;
                    i_offset += idat->i_pos + mp4_box_headersize(idat);
                }

                if( vlc_stream_Seek( p_demux->s, i_offset ) != VLC_SUCCESS )
                    break;
                *pp_append = vlc_stream_Block( p_demux->s, i_length );
            }
            /* Extents are 3:iloc reference */
            else if( BOXDATA(p_iloc)->p_items[i].i_construction_method == 2 )
            {
                /* FIXME ? That's totally untested and really complicated */
                uint32_t i_extent_index = BOXDATA(p_iloc)->p_items[i].p_extents[j].i_extent_index;
                if(i_extent_index == 0)
                    i_extent_index = 1; /* Inferred. Indexes start 1 */
                const MP4_Box_t *p_iref = MP4_BoxGet( p_sys->p_root, "meta/iref" );
                if(!p_iref)
                    break;
                for( const MP4_Box_t *p_refbox = p_iref->p_first;
                                      p_refbox; p_refbox = p_refbox->p_next )
                {
                    if( p_refbox->i_type != VLC_FOURCC('i','l','o','c') ||
                        BOXDATA(p_refbox)->i_from_item_id == i_item_id )
                        continue;

                    for( uint16_t k=0; k< BOXDATA(p_refbox)->i_reference_count; k++ )
                    {
                        if( --i_extent_index > 0 )
                            continue;
                        if( BOXDATA(p_refbox)->p_references[k].i_to_item_id != i_item_id )
                        {
                            *pp_append = ReadItemExtents(p_demux,
                                            BOXDATA(p_refbox)->p_references[k].i_to_item_id,
                                            NULL);
                        }
                    }

                    break;
                }
            }

            while( *pp_append )
                pp_append = &((*pp_append)->p_next);
        }
        break;
    }

    if( p_block )
        p_block = block_ChainGather( p_block );

    return p_block;
}