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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FLOAT_PRECISSION ; 
 int /*<<< orphan*/  IsGoodVal (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_LabA_FLT ; 
 int /*<<< orphan*/  TYPE_RGBA_FLT ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 

__attribute__((used)) static
cmsInt32Number ChecksRGB2LabFLT(void)
{
    cmsHPROFILE hSRGB = cmsCreate_sRGBProfile(DbgThread());
    cmsHPROFILE hLab  = cmsCreateLab4Profile(DbgThread(), NULL);

    cmsHTRANSFORM xform1 = cmsCreateTransform(DbgThread(), hSRGB, TYPE_RGBA_FLT, hLab, TYPE_LabA_FLT, 0, cmsFLAGS_NOCACHE|cmsFLAGS_NOOPTIMIZE);
    cmsHTRANSFORM xform2 = cmsCreateTransform(DbgThread(), hLab, TYPE_LabA_FLT, hSRGB, TYPE_RGBA_FLT, 0, cmsFLAGS_NOCACHE|cmsFLAGS_NOOPTIMIZE);

    cmsFloat32Number RGBA1[4], RGBA2[4], LabA[4];
    int i;


    for (i = 0; i <= 100; i++)
    {
        RGBA1[0] = i / 100.0F;
        RGBA1[1] = i / 100.0F;
        RGBA1[2] = i / 100.0F;
        RGBA1[3] = 0;

        cmsDoTransform(DbgThread(), xform1, RGBA1, LabA,  1);
        cmsDoTransform(DbgThread(), xform2, LabA, RGBA2, 1);

        if (!IsGoodVal("Float RGB->RGB", RGBA1[0], RGBA2[0], FLOAT_PRECISSION) ||
            !IsGoodVal("Float RGB->RGB", RGBA1[1], RGBA2[1], FLOAT_PRECISSION) ||
            !IsGoodVal("Float RGB->RGB", RGBA1[2], RGBA2[2], FLOAT_PRECISSION))
            return 0;
    }


    cmsDeleteTransform(DbgThread(), xform1);
    cmsDeleteTransform(DbgThread(), xform2);
    cmsCloseProfile(DbgThread(), hSRGB);
    cmsCloseProfile(DbgThread(), hLab);

    return 1;
}