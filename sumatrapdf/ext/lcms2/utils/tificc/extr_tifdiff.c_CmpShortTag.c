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
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFGetField (int /*<<< orphan*/ *,int,scalar_t__*) ; 

__attribute__((used)) static
int CmpShortTag(TIFF* tif1, TIFF* tif2, int tag)
{
        uint16 v1, v2;

        if (!TIFFGetField(tif1, tag, &v1)) return 0;
        if (!TIFFGetField(tif2, tag, &v2)) return 0;

        return v1 == v2;
}