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
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  cmsSigDeviceMfgDescTag ; 
 int cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckRemoveTag(void)
{
    cmsHPROFILE p;
    cmsMLU *mlu;
    int ret;

    p = cmsCreate_sRGBProfile(NULL);

    /* set value */
    mlu = cmsMLUalloc (NULL, 1);
    ret = cmsMLUsetASCII(DbgThread(), mlu, "en", "US", "bar");
    if (!ret) return 0;

    ret = cmsWriteTag(DbgThread(), p, cmsSigDeviceMfgDescTag, mlu);
    if (!ret) return 0;

    cmsMLUfree(DbgThread(), mlu);

    /* remove the tag  */
    ret = cmsWriteTag(DbgThread(), p, cmsSigDeviceMfgDescTag, NULL);
    if (!ret) return 0;

    /* THIS EXPLODES */
    cmsCloseProfile(DbgThread(), p);
    return 1;
}