#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct heif_private_t {int /*<<< orphan*/  p_root; } ;
struct TYPE_17__ {unsigned int i_visible_width; unsigned int i_visible_height; } ;
struct TYPE_19__ {TYPE_3__* p; TYPE_2__ format; } ;
typedef  TYPE_4__ picture_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
struct TYPE_16__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_20__ {int /*<<< orphan*/  i_codec; TYPE_1__ video; } ;
typedef  TYPE_5__ es_format_t ;
struct TYPE_21__ {scalar_t__ p_sys; } ;
typedef  TYPE_6__ demux_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_18__ {unsigned int i_lines; int /*<<< orphan*/  i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  int /*<<< orphan*/  MP4_Box_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_infe ; 
 int /*<<< orphan*/ * GetAtom (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MatchInfeID ; 
 int /*<<< orphan*/ * ReadItemExtents (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ SetupPicture (TYPE_6__*,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  VLC_CODEC_RGBA ; 
 int VLC_EGENERIC ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Clean (TYPE_5__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* image_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LoadGridImage( demux_t *p_demux,
                          image_handler_t *handler,
                          uint32_t i_pic_item_id,
                               uint8_t *p_buffer,
                               unsigned tile, unsigned gridcols,
                               unsigned imagewidth, unsigned imageheight )
{
    struct heif_private_t *p_sys = (void *) p_demux->p_sys;

    MP4_Box_t *p_infe = GetAtom( p_sys->p_root, NULL,
                                 ATOM_infe, "meta/iinf/infe",
                                 MatchInfeID, &i_pic_item_id );
    if( !p_infe )
        return VLC_EGENERIC;

    es_format_t fmt;
    es_format_Init(&fmt, UNKNOWN_ES, 0);

    const MP4_Box_t *p_shared_header = NULL;
    if( SetupPicture( p_demux, p_infe, &fmt, &p_shared_header ) != VLC_SUCCESS )
    {
        es_format_Clean( &fmt );
        return VLC_EGENERIC; /* Unsupported picture, goto next */
    }

    block_t *p_sample = ReadItemExtents( p_demux, i_pic_item_id,
                                         p_shared_header );
    if(!p_sample)
    {
        es_format_Clean( &fmt );
        return VLC_EGENERIC;
    }

    video_format_t decoded;
    video_format_Init( &decoded, VLC_CODEC_RGBA );

    fmt.video.i_chroma = fmt.i_codec;

    picture_t *p_picture = image_Read( handler, p_sample, &fmt, &decoded );

    es_format_Clean( &fmt );

    if ( !p_picture )
        return VLC_EGENERIC;

    const unsigned tilewidth = p_picture->format.i_visible_width;
    const unsigned tileheight = p_picture->format.i_visible_height;
    uint8_t *dstline = p_buffer;
    dstline += (tile / gridcols) * (imagewidth * tileheight * 4);
    for(;1;)
    {
        const unsigned offsetpxw = (tile % gridcols) * tilewidth;
        const unsigned offsetpxh = (tile / gridcols) * tileheight;
        if( offsetpxw > imagewidth )
            break;
        const uint8_t *srcline = p_picture->p[0].p_pixels;
        unsigned tocopylines = p_picture->p[0].i_lines;
        if(offsetpxh + tocopylines >= imageheight)
            tocopylines = imageheight - offsetpxh;
        for(unsigned i=0; i<tocopylines; i++)
        {
            size_t tocopypx = tilewidth;
            if( offsetpxw + tilewidth > imagewidth )
                tocopypx = imagewidth - offsetpxw;
            memcpy( &dstline[offsetpxw * 4], srcline, tocopypx * 4 );
            dstline += imagewidth * 4;
            srcline += p_picture->p[0].i_pitch;
        }

        break;
    }

    picture_Release( p_picture );

    return VLC_SUCCESS;
}