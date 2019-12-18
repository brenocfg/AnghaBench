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
typedef  scalar_t__ cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*,...) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsMLUalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsMLUdup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsMLUgetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*,int) ; 
 int /*<<< orphan*/  cmsMLUsetASCII (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  cmsMLUsetWide (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static
cmsInt32Number CheckMLU(void)
{
    cmsMLU* mlu, *mlu2, *mlu3;
    char Buffer[256], Buffer2[256];
    cmsInt32Number rc = 1;
    cmsInt32Number i;
    cmsHPROFILE h= NULL;

    // Allocate a MLU structure, no preferred size
    mlu = cmsMLUalloc(DbgThread(), 0);

    // Add some localizations
    cmsMLUsetWide(DbgThread(), mlu, "en", "US", L"Hello, world");
    cmsMLUsetWide(DbgThread(), mlu, "es", "ES", L"Hola, mundo");
    cmsMLUsetWide(DbgThread(), mlu, "fr", "FR", L"Bonjour, le monde");
    cmsMLUsetWide(DbgThread(), mlu, "ca", "CA", L"Hola, mon");


    // Check the returned string for each language

    cmsMLUgetASCII(DbgThread(), mlu, "en", "US", Buffer, 256);
    if (strcmp(Buffer, "Hello, world") != 0) rc = 0;


    cmsMLUgetASCII(DbgThread(), mlu, "es", "ES", Buffer, 256);
    if (strcmp(Buffer, "Hola, mundo") != 0) rc = 0;


    cmsMLUgetASCII(DbgThread(), mlu, "fr", "FR", Buffer, 256);
    if (strcmp(Buffer, "Bonjour, le monde") != 0) rc = 0;


    cmsMLUgetASCII(DbgThread(), mlu, "ca", "CA", Buffer, 256);
    if (strcmp(Buffer, "Hola, mon") != 0) rc = 0;

    if (rc == 0)
        Fail("Unexpected string '%s'", Buffer);

    // So far, so good.
    cmsMLUfree(DbgThread(), mlu);

    // Now for performance, allocate an empty struct
    mlu = cmsMLUalloc(DbgThread(), 0);

    // Fill it with several thousands of different lenguages
    for (i=0; i < 4096; i++) {

        char Lang[3];

        Lang[0] = (char) (i % 255);
        Lang[1] = (char) (i / 255);
        Lang[2] = 0;

        sprintf(Buffer, "String #%i", i);
        cmsMLUsetASCII(DbgThread(), mlu, Lang, Lang, Buffer);
    }

    // Duplicate it
    mlu2 = cmsMLUdup(DbgThread(), mlu);

    // Get rid of original
    cmsMLUfree(DbgThread(), mlu);

    // Check all is still in place
    for (i=0; i < 4096; i++) {

        char Lang[3];

        Lang[0] = (char)(i % 255);
        Lang[1] = (char)(i / 255);
        Lang[2] = 0;

        cmsMLUgetASCII(DbgThread(), mlu2, Lang, Lang, Buffer2, 256);
        sprintf(Buffer, "String #%i", i);

        if (strcmp(Buffer, Buffer2) != 0) { rc = 0; break; }
    }

    if (rc == 0)
        Fail("Unexpected string '%s'", Buffer2);

    // Check profile IO

    h = cmsOpenProfileFromFile(DbgThread(), "mlucheck.icc", "w");

    cmsSetProfileVersion(DbgThread(), h, 4.3);

    cmsWriteTag(DbgThread(), h, cmsSigProfileDescriptionTag, mlu2);
    cmsCloseProfile(DbgThread(), h);
    cmsMLUfree(DbgThread(), mlu2);


    h = cmsOpenProfileFromFile(DbgThread(), "mlucheck.icc", "r");

    mlu3 = (cmsMLU *) cmsReadTag(DbgThread(), h, cmsSigProfileDescriptionTag);
    if (mlu3 == NULL) { Fail("Profile didn't get the MLU\n"); rc = 0; goto Error; }

    // Check all is still in place
    for (i=0; i < 4096; i++) {

        char Lang[3];

        Lang[0] = (char) (i % 255);
        Lang[1] = (char) (i / 255);
        Lang[2] = 0;

        cmsMLUgetASCII(DbgThread(), mlu3, Lang, Lang, Buffer2, 256);
        sprintf(Buffer, "String #%i", i);

        if (strcmp(Buffer, Buffer2) != 0) { rc = 0; break; }
    }

    if (rc == 0) Fail("Unexpected string '%s'", Buffer2);

Error:

    if (h != NULL) cmsCloseProfile(DbgThread(), h);
    remove("mlucheck.icc");

    return rc;
}