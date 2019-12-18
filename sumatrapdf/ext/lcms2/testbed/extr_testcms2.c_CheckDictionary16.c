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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/ * cmsHANDLE ;
struct TYPE_5__ {int /*<<< orphan*/ * Value; int /*<<< orphan*/ * Name; } ;
typedef  TYPE_1__ cmsDICTentry ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsDictAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsDictAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDictFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cmsDictGetEntryList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cmsDictNextEntry (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigMetaTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static
cmsInt32Number CheckDictionary16(cmsInt32Number Pass,  cmsHPROFILE hProfile)
{
      cmsHANDLE hDict;
      const cmsDICTentry* e;
      switch (Pass) {

        case 1:
            hDict = cmsDictAlloc(DbgThread());
            cmsDictAddEntry(DbgThread(), hDict, L"Name0",  NULL, NULL, NULL);
            cmsDictAddEntry(DbgThread(), hDict, L"Name1",  L"", NULL, NULL);
            cmsDictAddEntry(DbgThread(), hDict, L"Name",  L"String", NULL, NULL);
            cmsDictAddEntry(DbgThread(), hDict, L"Name2", L"12",    NULL, NULL);
            if (!cmsWriteTag(DbgThread(), hProfile, cmsSigMetaTag, hDict)) return 0;
            cmsDictFree(DbgThread(), hDict);
            return 1;


        case 2:

             hDict = cmsReadTag(DbgThread(), hProfile, cmsSigMetaTag);
             if (hDict == NULL) return 0;
             e = cmsDictGetEntryList(DbgThread(), hDict);
             if (memcmp(e ->Name, L"Name2", sizeof(wchar_t) * 5) != 0) return 0;
             if (memcmp(e ->Value, L"12",  sizeof(wchar_t) * 2) != 0) return 0;
             e = cmsDictNextEntry(DbgThread(), e);
             if (memcmp(e ->Name, L"Name", sizeof(wchar_t) * 4) != 0) return 0;
             if (memcmp(e ->Value, L"String",  sizeof(wchar_t) * 5) != 0) return 0;
             e = cmsDictNextEntry(DbgThread(), e);
             if (memcmp(e ->Name, L"Name1", sizeof(wchar_t) *5) != 0) return 0;
             if (e ->Value == NULL) return 0;
             if (*e->Value != 0) return 0;
             e = cmsDictNextEntry(DbgThread(), e);
             if (memcmp(e ->Name, L"Name0", sizeof(wchar_t) * 5) != 0) return 0;
             if (e ->Value != NULL) return 0;
             return 1;


        default:;
    }

    return 0;
}