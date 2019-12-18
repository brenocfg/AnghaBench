#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Desc; void* Ucr; void* Bg; } ;
typedef  TYPE_1__ cmsUcrBg ;
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 void* cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsMLUalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsNoCountry ; 
 int /*<<< orphan*/  cmsNoLanguage ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckUcrBg(cmsInt32Number Pass,  cmsHPROFILE hProfile, cmsTagSignature tag)
{
    cmsUcrBg *Pt, m;
    cmsInt32Number rc;
    char Buffer[256];

    switch (Pass) {

        case 1:
            m.Ucr = cmsBuildGamma(DbgThread(), 2.4);
            m.Bg  = cmsBuildGamma(DbgThread(), -2.2);
            m.Desc = cmsMLUalloc(DbgThread(), 1);
            cmsMLUsetASCII(DbgThread(), m.Desc,  cmsNoLanguage, cmsNoCountry, "test UCR/BG");
            rc = cmsWriteTag(DbgThread(), hProfile, tag, &m);
            cmsMLUfree(DbgThread(), m.Desc);
            cmsFreeToneCurve(DbgThread(), m.Bg);
            cmsFreeToneCurve(DbgThread(), m.Ucr);
            return rc;


        case 2:
            Pt = (cmsUcrBg *) cmsReadTag(DbgThread(), hProfile, tag);
            if (Pt == NULL) return 0;

            cmsMLUgetASCII(DbgThread(), Pt ->Desc, cmsNoLanguage, cmsNoCountry, Buffer, 256);
            if (strcmp(Buffer, "test UCR/BG") != 0) return 0;
            return 1;

        default:
            return 0;
    }
}