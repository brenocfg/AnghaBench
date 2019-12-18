#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int OPJ_UINT8 ;
typedef  int OPJ_UINT32 ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static OPJ_BOOL bmp_read_rle4_data(FILE* IN, OPJ_UINT8* pData,
                                   OPJ_UINT32 stride, OPJ_UINT32 width, OPJ_UINT32 height)
{
    OPJ_UINT32 x, y;
    OPJ_UINT8 *pix;
    const OPJ_UINT8 *beyond;

    beyond = pData + stride * height;
    pix = pData;
    x = y = 0U;
    while (y < height) {
        int c = getc(IN);
        if (c == EOF) {
            break;
        }

        if (c) { /* encoded mode */
            int j;
            OPJ_UINT8 c1 = (OPJ_UINT8)getc(IN);

            for (j = 0; (j < c) && (x < width) &&
                    ((OPJ_SIZE_T)pix < (OPJ_SIZE_T)beyond); j++, x++, pix++) {
                *pix = (OPJ_UINT8)((j & 1) ? (c1 & 0x0fU) : ((c1 >> 4) & 0x0fU));
            }
        } else { /* absolute mode */
            c = getc(IN);
            if (c == EOF) {
                break;
            }

            if (c == 0x00) { /* EOL */
                x = 0;
                y++;
                pix = pData + y * stride;
            } else if (c == 0x01) { /* EOP */
                break;
            } else if (c == 0x02) { /* MOVE by dxdy */
                c = getc(IN);
                x += (OPJ_UINT32)c;
                c = getc(IN);
                y += (OPJ_UINT32)c;
                pix = pData + y * stride + x;
            } else { /* 03 .. 255 : absolute mode */
                int j;
                OPJ_UINT8 c1 = 0U;

                for (j = 0; (j < c) && (x < width) &&
                        ((OPJ_SIZE_T)pix < (OPJ_SIZE_T)beyond); j++, x++, pix++) {
                    if ((j & 1) == 0) {
                        c1 = (OPJ_UINT8)getc(IN);
                    }
                    *pix = (OPJ_UINT8)((j & 1) ? (c1 & 0x0fU) : ((c1 >> 4) & 0x0fU));
                }
                if (((c & 3) == 1) || ((c & 3) == 2)) { /* skip padding byte */
                    getc(IN);
                }
            }
        }
    }  /* while(y < height) */
    return OPJ_TRUE;
}