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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  SubTest (char const*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static
cmsInt32Number OneVirtual(cmsHPROFILE h, const char* SubTestTxt, const char* FileName)
{
    SubTest(SubTestTxt);
    if (h == NULL) return 0;

    if (!cmsSaveProfileToFile(DbgThread(), h, FileName)) return 0;
    cmsCloseProfile(DbgThread(), h);

    h = cmsOpenProfileFromFile(DbgThread(), FileName, "r");
    if (h == NULL) return 0;

    cmsCloseProfile(DbgThread(), h);
    return 1;
}