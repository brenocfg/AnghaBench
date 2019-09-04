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
typedef  int /*<<< orphan*/  GifFileType ;
typedef  int GifByteType ;

/* Variables and functions */
 int GIF_ERROR ; 
 int GIF_OK ; 
 int READ (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static int
DGifBufferedInput(GifFileType * GifFile,
                  GifByteType * Buf,
                  GifByteType * NextByte) {

    if (Buf[0] == 0) {
        /* Needs to read the next buffer - this one is empty: */
        if (READ(GifFile, Buf, 1) != 1) {
            return GIF_ERROR;
        }
        /* There shouldn't be any empty data blocks here as the LZW spec
         * says the LZW termination code should come first.  Therefore we
         * shouldn't be inside this routine at that point.
         */
        if (Buf[0] == 0) {
            return GIF_ERROR;
        }
        if (READ(GifFile, &Buf[1], Buf[0]) != Buf[0]) {
            return GIF_ERROR;
        }
        *NextByte = Buf[1];
        Buf[1] = 2;    /* We use now the second place as last char read! */
        Buf[0]--;
    } else {
        *NextByte = Buf[Buf[1]++];
        Buf[0]--;
    }

    return GIF_OK;
}