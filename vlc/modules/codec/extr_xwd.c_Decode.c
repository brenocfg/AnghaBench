#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_22__ {scalar_t__ date; int b_progressive; TYPE_4__* p; } ;
typedef  TYPE_5__ picture_t ;
struct TYPE_26__ {int i_width; int i_bits_per_pixel; scalar_t__ const i_height; } ;
struct TYPE_20__ {TYPE_9__ video; } ;
struct TYPE_18__ {int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; } ;
struct TYPE_19__ {TYPE_1__ video; } ;
struct TYPE_23__ {TYPE_3__ fmt_out; TYPE_2__ fmt_in; } ;
typedef  TYPE_6__ decoder_t ;
struct TYPE_24__ {scalar_t__ i_pts; scalar_t__ i_buffer; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_7__ block_t ;
struct TYPE_25__ {int /*<<< orphan*/  bytes_per_line; int /*<<< orphan*/  pixmap_height; int /*<<< orphan*/  pixmap_width; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  pixmap_depth; int /*<<< orphan*/  ncolors; int /*<<< orphan*/  pixmap_format; int /*<<< orphan*/  file_version; int /*<<< orphan*/  header_size; } ;
typedef  TYPE_8__ XWDFileHeader ;
struct TYPE_21__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_CODEC_ARGB ; 
 scalar_t__ VLC_CODEC_RGB15 ; 
 scalar_t__ VLC_CODEC_RGB16 ; 
 scalar_t__ VLC_CODEC_RGB24 ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
 scalar_t__ VLC_CODEC_RGB8 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int XWD_FILE_VERSION ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 TYPE_5__* decoder_NewPicture (TYPE_6__*) ; 
 int /*<<< orphan*/  decoder_QueueVideo (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ decoder_UpdateVideoFormat (TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int sz_XWDColor ; 
 scalar_t__ sz_XWDheader ; 
 int /*<<< orphan*/  video_format_Setup (TYPE_9__*,scalar_t__,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Decode (decoder_t *dec, block_t *block)
{
    picture_t *pic = NULL;

    if (block == NULL) /* No Drain */
        return VLCDEC_SUCCESS;

    if (block->i_pts == VLC_TICK_INVALID)
        goto drop; /* undated block, should never happen */
    if (block->i_buffer < sz_XWDheader)
        goto drop;

    /* Skip XWD header */
    const XWDFileHeader *hdr = (const void *)block->p_buffer;
    uint32_t hdrlen = ntohl(hdr->header_size);
    if (hdrlen < sz_XWDheader
     || ntohl(hdr->file_version) < XWD_FILE_VERSION
     || ntohl(hdr->pixmap_format) != 2 /* ZPixmap */)
        goto drop;

    hdrlen += ntohl(hdr->ncolors) * sz_XWDColor;
    if (hdrlen > block->i_buffer)
        goto drop;
    block->p_buffer += hdrlen;
    block->i_buffer -= hdrlen;

    /* Parse XWD header */
    vlc_fourcc_t chroma = 0;
    switch (ntohl(hdr->pixmap_depth))
    {
        case 8:
            if (ntohl(hdr->bits_per_pixel) == 8)
                chroma = VLC_CODEC_RGB8;
            break;
        case 15:
            if (ntohl(hdr->bits_per_pixel) == 16)
                chroma = VLC_CODEC_RGB15;
            break;
        case 16:
            if (ntohl(hdr->bits_per_pixel) == 16)
                chroma = VLC_CODEC_RGB16;
            break;
        case 24:
            switch (ntohl(hdr->bits_per_pixel))
            {
                case 32: chroma = VLC_CODEC_RGB32; break;
                case 24: chroma = VLC_CODEC_RGB24; break;
            }
            break;
        case 32:
            if (ntohl(hdr->bits_per_pixel) == 32)
                chroma = VLC_CODEC_ARGB;
            break;
    }
    /* TODO: check image endianess, set RGB mask */
    if (!chroma)
        goto drop;

    video_format_Setup(&dec->fmt_out.video, chroma,
                       ntohl(hdr->pixmap_width), ntohl(hdr->pixmap_height),
                       ntohl(hdr->pixmap_width), ntohl(hdr->pixmap_height),
                       dec->fmt_in.video.i_sar_num,
                       dec->fmt_in.video.i_sar_den);

    const size_t copy = dec->fmt_out.video.i_width
                        * (dec->fmt_out.video.i_bits_per_pixel / 8);
    const uint32_t pitch = ntohl(hdr->bytes_per_line);

    /* Build picture */
    if (pitch < copy
     || (block->i_buffer / pitch) < dec->fmt_out.video.i_height)
        goto drop;

    if (decoder_UpdateVideoFormat(dec))
        goto drop;
    pic = decoder_NewPicture(dec);
    if (pic == NULL)
        goto drop;

    const uint8_t *in = block->p_buffer;
    uint8_t *out = pic->p->p_pixels;
    for (unsigned i = 0; i < dec->fmt_out.video.i_height; i++)
    {
        memcpy(out, in, copy);
        in += pitch;
        out += pic->p->i_pitch;
    }
    pic->date = block->i_pts;
    pic->b_progressive = true;

drop:
    block_Release(block);
    decoder_QueueVideo(dec, pic);
    return VLCDEC_SUCCESS;
}