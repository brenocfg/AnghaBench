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
typedef  int /*<<< orphan*/  cmsMLU ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/ * cmsHANDLE ;
struct TYPE_5__ {int /*<<< orphan*/  DisplayName; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ cmsDICTentry ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,char*) ; 
 int /*<<< orphan*/  cmsDictAddEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsDictAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDictFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cmsDictGetEntryList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cmsDictNextEntry (int /*<<< orphan*/ ,TYPE_1__ const*) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int) ; 
 int /*<<< orphan*/  cmsMLUsetWide (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/ * cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigMetaTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckDictionary24(cmsInt32Number Pass,  cmsHPROFILE hProfile)
{
    cmsHANDLE hDict;
    const cmsDICTentry* e;
    cmsMLU* DisplayName;
    char Buffer[256];
    cmsInt32Number rc = 1;

    switch (Pass) {

    case 1:
        hDict = cmsDictAlloc(DbgThread());

        DisplayName = cmsMLUalloc(DbgThread(), 0);

        cmsMLUsetWide(DbgThread(), DisplayName, "en", "US", L"Hello, world");
        cmsMLUsetWide(DbgThread(), DisplayName, "es", "ES", L"Hola, mundo");
        cmsMLUsetWide(DbgThread(), DisplayName, "fr", "FR", L"Bonjour, le monde");
        cmsMLUsetWide(DbgThread(), DisplayName, "ca", "CA", L"Hola, mon");

        cmsDictAddEntry(DbgThread(), hDict, L"Name",  L"String", DisplayName, NULL);
        cmsMLUfree(DbgThread(), DisplayName);

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

        cmsMLUgetASCII(DbgThread(), e->DisplayName, "en", "US", Buffer, 256);
        if (strcmp(Buffer, "Hello, world") != 0) rc = 0;


        cmsMLUgetASCII(DbgThread(), e->DisplayName, "es", "ES", Buffer, 256);
        if (strcmp(Buffer, "Hola, mundo") != 0) rc = 0;


        cmsMLUgetASCII(DbgThread(), e->DisplayName, "fr", "FR", Buffer, 256);
        if (strcmp(Buffer, "Bonjour, le monde") != 0) rc = 0;


        cmsMLUgetASCII(DbgThread(), e->DisplayName, "ca", "CA", Buffer, 256);
        if (strcmp(Buffer, "Hola, mon") != 0) rc = 0;

        if (rc == 0)
            Fail("Unexpected string '%s'", Buffer);
        return 1;

    default:;
    }

    return 0;
}