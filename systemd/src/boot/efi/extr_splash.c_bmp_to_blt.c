#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bmp_map {int red; int green; int blue; } ;
struct bmp_dib {scalar_t__ y; scalar_t__ x; int depth; } ;
typedef  scalar_t__ UINTN ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;
struct TYPE_3__ {int Red; int Green; int Blue; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  TYPE_1__ EFI_GRAPHICS_OUTPUT_BLT_PIXEL ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_SUCCESS ; 
 int /*<<< orphan*/  pixel_blend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

EFI_STATUS bmp_to_blt(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *buf,
                      struct bmp_dib *dib, struct bmp_map *map,
                      UINT8 *pixmap) {
        UINT8 *in;
        UINTN y;

        /* transform and copy pixels */
        in = pixmap;
        for (y = 0; y < dib->y; y++) {
                EFI_GRAPHICS_OUTPUT_BLT_PIXEL *out;
                UINTN row_size;
                UINTN x;

                out = &buf[(dib->y - y - 1) * dib->x];
                for (x = 0; x < dib->x; x++, in++, out++) {
                        switch (dib->depth) {
                        case 1: {
                                UINTN i;

                                for (i = 0; i < 8 && x < dib->x; i++) {
                                        out->Red = map[((*in) >> (7 - i)) & 1].red;
                                        out->Green = map[((*in) >> (7 - i)) & 1].green;
                                        out->Blue = map[((*in) >> (7 - i)) & 1].blue;
                                        out++;
                                        x++;
                                }
                                out--;
                                x--;
                                break;
                        }

                        case 4: {
                                UINTN i;

                                i = (*in) >> 4;
                                out->Red = map[i].red;
                                out->Green = map[i].green;
                                out->Blue = map[i].blue;
                                if (x < (dib->x - 1)) {
                                        out++;
                                        x++;
                                        i = (*in) & 0x0f;
                                        out->Red = map[i].red;
                                        out->Green = map[i].green;
                                        out->Blue = map[i].blue;
                                }
                                break;
                        }

                        case 8:
                                out->Red = map[*in].red;
                                out->Green = map[*in].green;
                                out->Blue = map[*in].blue;
                                break;

                        case 16: {
                                UINT16 i = *(UINT16 *) in;

                                out->Red = (i & 0x7c00) >> 7;
                                out->Green = (i & 0x3e0) >> 2;
                                out->Blue = (i & 0x1f) << 3;
                                in += 1;
                                break;
                        }

                        case 24:
                                out->Red = in[2];
                                out->Green = in[1];
                                out->Blue = in[0];
                                in += 2;
                                break;

                        case 32: {
                                UINT32 i = *(UINT32 *) in;

                                pixel_blend((UINT32 *)out, i);

                                in += 3;
                                break;
                        }
                        }
                }

                /* add row padding; new lines always start at 32 bit boundary */
                row_size = in - pixmap;
                in += ((row_size + 3) & ~3) - row_size;
        }

        return EFI_SUCCESS;
}