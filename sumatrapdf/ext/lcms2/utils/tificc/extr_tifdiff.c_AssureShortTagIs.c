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
typedef  int uint16 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  FatalError (char*,char const*) ; 
 int /*<<< orphan*/  TIFFGetField (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static
void AssureShortTagIs(TIFF* tif1, TIFF* tiff2, int tag, int Val, const char* Error)
{
        uint16 v1;


        if (!TIFFGetField(tif1, tag, &v1)) goto Err;
        if (v1 != Val) goto Err;

        if (!TIFFGetField(tiff2, tag, &v1)) goto Err;
        if (v1 != Val) goto Err;

        return;
Err:
        FatalError("%s is not proper", Error);
}