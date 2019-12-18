#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  void* cmsUInt16Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  scalar_t__ cmsFloat64Number ;
typedef  scalar_t__ clock_t ;
struct TYPE_5__ {void* b; void* g; void* r; } ;
typedef  TYPE_1__ Scanline_rgb16 ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Die (char*) ; 
 int /*<<< orphan*/  PrintPerformance (int,int,scalar_t__) ; 
 int /*<<< orphan*/  TYPE_RGB_16 ; 
 int /*<<< orphan*/  TitlePerformance (char const*) ; 
 scalar_t__ clock () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static
void SpeedTest16bits(const char * Title, cmsHPROFILE hlcmsProfileIn, cmsHPROFILE hlcmsProfileOut, cmsInt32Number Intent)
{
    cmsInt32Number r, g, b, j;
    clock_t atime;
    cmsFloat64Number diff;
    cmsHTRANSFORM hlcmsxform;
    Scanline_rgb16 *In;
    cmsUInt32Number Mb;

    if (hlcmsProfileIn == NULL || hlcmsProfileOut == NULL)
        Die("Unable to open profiles");

    hlcmsxform  = cmsCreateTransform(DbgThread(), hlcmsProfileIn, TYPE_RGB_16,
        hlcmsProfileOut, TYPE_RGB_16, Intent, cmsFLAGS_NOCACHE);
    cmsCloseProfile(DbgThread(), hlcmsProfileIn);
    cmsCloseProfile(DbgThread(), hlcmsProfileOut);

    Mb = 256*256*256 * sizeof(Scanline_rgb16);

    In = (Scanline_rgb16*) malloc(Mb);

    j = 0;
    for (r=0; r < 256; r++)
        for (g=0; g < 256; g++)
            for (b=0; b < 256; b++) {

                In[j].r = (cmsUInt16Number) ((r << 8) | r);
                In[j].g = (cmsUInt16Number) ((g << 8) | g);
                In[j].b = (cmsUInt16Number) ((b << 8) | b);

                j++;
            }


    TitlePerformance(Title);

    atime = clock();

    cmsDoTransform(DbgThread(), hlcmsxform, In, In, 256*256*256);

    diff = clock() - atime;
    free(In);

    PrintPerformance(Mb, sizeof(Scanline_rgb16), diff);
    cmsDeleteTransform(DbgThread(), hlcmsxform);

}