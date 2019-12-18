#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t i_width; size_t i_height; } ;
struct TYPE_7__ {TYPE_2__* p; TYPE_1__ format; } ;
typedef  TYPE_3__ picture_t ;
struct TYPE_6__ {size_t i_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 size_t TILE_GROUP_SIZE ; 
 size_t TILE_HEIGHT ; 
 size_t const TILE_SIZE ; 
 size_t TILE_WIDTH ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t const tile_pos (size_t,size_t,size_t const,size_t const) ; 

void qcom_convert(const uint8_t *src, picture_t *pic)
{
    size_t width = pic->format.i_width;
    size_t pitch = pic->p[0].i_pitch;
    size_t height = pic->format.i_height;

    const size_t tile_w = (width - 1) / TILE_WIDTH + 1;
    const size_t tile_w_align = (tile_w + 1) & ~1;

    const size_t tile_h_luma = (height - 1) / TILE_HEIGHT + 1;
    const size_t tile_h_chroma = (height / 2 - 1) / TILE_HEIGHT + 1;

    size_t luma_size = tile_w_align * tile_h_luma * TILE_SIZE;

#define TILE_GROUP_SIZE (4 * TILE_SIZE)
    if((luma_size % TILE_GROUP_SIZE) != 0)
        luma_size = (((luma_size - 1) / TILE_GROUP_SIZE) + 1) * TILE_GROUP_SIZE;

    for(size_t y = 0; y < tile_h_luma; y++) {
        size_t row_width = width;
        for(size_t x = 0; x < tile_w; x++) {
            /* luma source pointer for this tile */
            const uint8_t *src_luma  = src
                + tile_pos(x, y,tile_w_align, tile_h_luma) * TILE_SIZE;

            /* chroma source pointer for this tile */
            const uint8_t *src_chroma = src + luma_size
                + tile_pos(x, y/2, tile_w_align, tile_h_chroma) * TILE_SIZE;
            if (y & 1)
                src_chroma += TILE_SIZE/2;

            /* account for right columns */
            size_t tile_width = row_width;
            if (tile_width > TILE_WIDTH)
                tile_width = TILE_WIDTH;

            /* account for bottom rows */
            size_t tile_height = height;
            if (tile_height > TILE_HEIGHT)
                tile_height = TILE_HEIGHT;

            /* dest luma memory index for this tile */
            size_t luma_idx = y * TILE_HEIGHT * pitch + x * TILE_WIDTH;

            /* dest chroma memory index for this tile */
            /* XXX: remove divisions */
            size_t chroma_idx = (luma_idx / pitch) * pitch/2 + (luma_idx % pitch);

            tile_height /= 2; // we copy 2 luma lines at once
            while (tile_height--) {
                memcpy(&pic->p[0].p_pixels[luma_idx], src_luma, tile_width);
                src_luma += TILE_WIDTH;
                luma_idx += pitch;

                memcpy(&pic->p[0].p_pixels[luma_idx], src_luma, tile_width);
                src_luma += TILE_WIDTH;
                luma_idx += pitch;

                memcpy(&pic->p[1].p_pixels[chroma_idx], src_chroma, tile_width);
                src_chroma += TILE_WIDTH;
                chroma_idx += pitch;
            }
            row_width -= TILE_WIDTH;
        }
        height -= TILE_HEIGHT;
    }
}