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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/ * cmsHANDLE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmsSaveProfileToMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigMetaTag ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsInt32Number CheckMeta(void)
{
    char *data;
    cmsHANDLE dict;
    cmsHPROFILE p;
    cmsUInt32Number clen;
    FILE *fp;
    int rc;

    /* open file */
    p = cmsOpenProfileFromFile(DbgThread(), "ibm-t61.icc", "r");
    if (p == NULL) return 0;

    /* read dictionary, but don't do anything with the value */
    //COMMENT OUT THE NEXT TWO LINES AND IT WORKS FINE!!!
    dict = cmsReadTag(DbgThread(), p, cmsSigMetaTag);
    if (dict == NULL) return 0;

    /* serialize profile to memory */
    rc = cmsSaveProfileToMem(DbgThread(), p, NULL, &clen);
    if (!rc) return 0;

    data = (char*) malloc(clen);
    rc = cmsSaveProfileToMem(DbgThread(), p, data, &clen);
    if (!rc) return 0;

    /* write the memory blob to a file */
    //NOTE: The crash does not happen if cmsSaveProfileToFile() is used */
    fp = fopen("new.icc", "wb");
    fwrite(data, 1, clen, fp);
    fclose(fp);
    free(data);

    cmsCloseProfile(DbgThread(), p);

    /* open newly created file and read metadata */
    p = cmsOpenProfileFromFile(DbgThread(), "new.icc", "r");
    //ERROR: Bad dictionary Name/Value
    //ERROR: Corrupted tag 'meta'
    //test: test.c:59: main: Assertion `dict' failed.
    dict = cmsReadTag(DbgThread(), p, cmsSigMetaTag);
   if (dict == NULL) return 0;

   cmsCloseProfile(DbgThread(), p);
    return 1;
}