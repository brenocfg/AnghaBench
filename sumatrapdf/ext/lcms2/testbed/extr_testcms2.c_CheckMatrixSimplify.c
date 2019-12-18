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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  TYPE_RGB_8 ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransformStride (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned char*,int,int) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckMatrixSimplify(void)
{

       cmsHPROFILE pIn;
       cmsHPROFILE pOut;
       cmsHTRANSFORM t;
       unsigned char buf[3] = { 127, 32, 64 };


       pIn = cmsCreate_sRGBProfile(DbgThread());
       pOut = cmsOpenProfileFromFile(DbgThread(), "ibm-t61.icc", "r");
       if (pIn == NULL || pOut == NULL)
              return 0;

       t = cmsCreateTransform(DbgThread(), pIn, TYPE_RGB_8, pOut, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
       cmsDoTransformStride(DbgThread(), t, buf, buf, 1, 1);
       cmsDeleteTransform(DbgThread(), t);
       cmsCloseProfile(DbgThread(), pIn);
       cmsCloseProfile(DbgThread(), pOut);


       return buf[0] == 144 && buf[1] == 0 && buf[2] == 69;
}