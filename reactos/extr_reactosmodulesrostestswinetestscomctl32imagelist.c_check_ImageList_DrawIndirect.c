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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  IMAGELISTDRAWPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  colour_match (int,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  pImageList_DrawIndirect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_ImageList_DrawIndirect(IMAGELISTDRAWPARAMS *ildp, UINT32 *bits,
                                         UINT32 expected, int line)
{
    bits[0] = 0x00FFFFFF;
    pImageList_DrawIndirect(ildp);
    ok(colour_match(bits[0], expected),
       "ImageList_DrawIndirect: Pixel %08X, Expected a close match to %08X from line %d\n",
       bits[0] & 0x00FFFFFF, expected, line);
}