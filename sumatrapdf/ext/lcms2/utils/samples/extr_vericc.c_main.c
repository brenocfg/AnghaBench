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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;

/* Variables and functions */
 int PrintUsage () ; 
 int /*<<< orphan*/  atof (char*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int main(int argc, char *argv[])
{
       cmsHPROFILE hProfile;
	   char* ptr;
	   cmsFloat64Number Version;

	   if (argc != 3)  return PrintUsage();

	   ptr = argv[1];
	   if (strncmp(ptr, "--r", 3) != 0) return PrintUsage();
	   ptr += 3;
	   if (!*ptr) { fprintf(stderr, "Wrong version number\n"); return 1; }

	   Version = atof(ptr); 

	   hProfile = cmsOpenProfileFromFile(argv[2], "r");
	   if (hProfile == NULL) { fprintf(stderr, "'%s': cannot open\n", argv[2]); return 1; }

	   cmsSetProfileVersion(hProfile, Version);
	   cmsSaveProfileToFile(hProfile, "$$tmp.icc");
	   cmsCloseProfile(hProfile);

	   remove(argv[2]);
	   rename("$$tmp.icc", argv[2]);
	   return 0;


}