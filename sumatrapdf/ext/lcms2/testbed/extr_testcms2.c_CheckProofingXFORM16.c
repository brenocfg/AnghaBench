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
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Check16linearXFORM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_RGB_16 ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateProofingTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_SOFTPROOFING ; 

__attribute__((used)) static
cmsInt32Number CheckProofingXFORM16(void)
{
    cmsHPROFILE hAbove;
    cmsHTRANSFORM xform;
    cmsInt32Number rc;

    hAbove = Create_AboveRGB();
    xform =  cmsCreateProofingTransform(DbgThread(), hAbove, TYPE_RGB_16, hAbove, TYPE_RGB_16, hAbove,
                                INTENT_RELATIVE_COLORIMETRIC, INTENT_RELATIVE_COLORIMETRIC, cmsFLAGS_SOFTPROOFING|cmsFLAGS_NOCACHE);
    cmsCloseProfile(DbgThread(), hAbove);
    rc = Check16linearXFORM(xform, 3);
    cmsDeleteTransform(DbgThread(), xform);
    return rc;
}