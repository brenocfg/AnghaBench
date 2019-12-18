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
typedef  int cmsUInt32Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  scalar_t__ cmsFloat64Number ;
typedef  int cmsFloat32Number ;
typedef  scalar_t__ clock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Die (char*) ; 
 int /*<<< orphan*/  PrintPerformance (int,int,scalar_t__) ; 
 int /*<<< orphan*/  TYPE_GRAY_FLT ; 
 int /*<<< orphan*/  TitlePerformance (char const*) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static
void SpeedTest32bitsGray(const char * Title, cmsHPROFILE hlcmsProfileIn, cmsHPROFILE hlcmsProfileOut, cmsInt32Number Intent)
{
    cmsInt32Number r, g, b, j;
    clock_t atime;
    cmsFloat64Number diff;
    cmsHTRANSFORM hlcmsxform;
    cmsFloat32Number *In;
    cmsUInt32Number Mb;
    cmsUInt32Number Interval = 4; // Power of 2 number to increment r,g,b values by in the loops to keep the test duration practically short
    cmsUInt32Number NumPixels;

    if (hlcmsProfileIn == NULL || hlcmsProfileOut == NULL)
        Die("Unable to open profiles");

    hlcmsxform  = cmsCreateTransform(DbgThread(), hlcmsProfileIn,
        TYPE_GRAY_FLT, hlcmsProfileOut, TYPE_GRAY_FLT, Intent, cmsFLAGS_NOCACHE);
    cmsCloseProfile(DbgThread(), hlcmsProfileIn);
    cmsCloseProfile(DbgThread(), hlcmsProfileOut);

    NumPixels = 256 / Interval * 256 / Interval * 256 / Interval;
    Mb = NumPixels * sizeof(cmsFloat32Number);

    In = (cmsFloat32Number*) malloc(Mb);

    j = 0;
    for (r = 0; r < 256; r += Interval)
        for (g = 0; g < 256; g += Interval)
            for (b = 0; b < 256; b += Interval) {

                In[j] = ((r + g + b) / 768.0f);

                j++;
            }

    TitlePerformance(Title);

    atime = clock();

    cmsDoTransform(DbgThread(), hlcmsxform, In, In, NumPixels);

    diff = clock() - atime;
    free(In);

    PrintPerformance(Mb, sizeof(cmsFloat32Number), diff);
    cmsDeleteTransform(DbgThread(), hlcmsxform);
}