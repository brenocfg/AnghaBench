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
 int /*<<< orphan*/  CheckOutGray (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * Create_Gray22 () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_GRAY_8 ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number CheckOutputGray(void)
{
    cmsHPROFILE hGray = Create_Gray22();
    cmsHPROFILE hLab  = cmsCreateLab4Profile(DbgThread(), NULL);
    cmsHTRANSFORM xform;

    if (hGray == NULL || hLab == NULL) return 0;

    xform = cmsCreateTransform(DbgThread(), hLab, TYPE_Lab_DBL, hGray, TYPE_GRAY_8, INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsCloseProfile(DbgThread(), hGray); cmsCloseProfile(DbgThread(), hLab);

    if (!CheckOutGray(xform, 0, 0)) return 0;
    if (!CheckOutGray(xform, 100, 255)) return 0;

    if (!CheckOutGray(xform, 20, 52)) return 0;
    if (!CheckOutGray(xform, 50, 118)) return 0;


    cmsDeleteTransform(DbgThread(), xform);
    return 1;
}