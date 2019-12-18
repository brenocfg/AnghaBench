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
typedef  int cmsUInt8Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_RGB_8 ; 
 double VecDist (int*,int*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ *,int*,int*,int) ; 
 int /*<<< orphan*/  cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 double sqrt (double) ; 

int main(int  argc, char* argv[])
{

    int r, g, b;
    cmsUInt8Number RGB[3], RGB_OUT[3];
    cmsHTRANSFORM xform;
    cmsHPROFILE hProfile;
    double err, SumX=0, SumX2=0, Peak = 0, n = 0;


    if (argc != 2) {
        printf("roundtrip <RGB icc profile>\n");
        return 1;
    }

    hProfile = cmsOpenProfileFromFile(argv[1], "r");
    if (hProfile == NULL)
    {
        printf("invalid profile\n");
        return 1;
    }

    xform = cmsCreateTransform(hProfile,TYPE_RGB_8, hProfile, TYPE_RGB_8, INTENT_RELATIVE_COLORIMETRIC, cmsFLAGS_NOOPTIMIZE);
    if (xform == NULL)
    {
        printf("Not a valid RGB profile\n");
        return 1;
    }

    for (r=0; r< 256; r++) {
        printf("%d  \r", r);
        for (g=0; g < 256; g++) {
            for (b=0; b < 256; b++) {

                RGB[0] = r;
                RGB[1] = g;
                RGB[2] = b;

                cmsDoTransform(xform, RGB, RGB_OUT, 1);

                err = VecDist(RGB, RGB_OUT);

                SumX  += err;
                SumX2 += err * err;
                n += 1.0;
                if (err > Peak)
                    Peak = err;

            }
        }
    }

    printf("Average %g\n", SumX / n);
    printf("Max %g\n", Peak);
    printf("Std  %g\n", sqrt((n*SumX2 - SumX * SumX) / (n*(n-1))));
    cmsCloseProfile(hProfile);
    cmsDeleteTransform(xform);

    return 0;
}