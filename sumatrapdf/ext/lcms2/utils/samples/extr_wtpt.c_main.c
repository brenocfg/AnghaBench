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
typedef  int /*<<< orphan*/  cmsCIEXYZ ;

/* Variables and functions */
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  InitUtils (char*) ; 
 int /*<<< orphan*/  ShowWhitePoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/ * cmsReadTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigMediaWhitePointTag ; 
 int xoptind ; 

int main(int argc, char *argv[])
{
       int nargs;

       InitUtils("wtpt");
       
       HandleSwitches(argc, argv);

       nargs = (argc - xoptind);

       if (nargs != 1)
              Help();

       else {
              cmsCIEXYZ* WtPt;
              cmsHPROFILE hProfile = cmsOpenProfileFromFile(argv[xoptind], "r");  
              if (hProfile == NULL) return 1;

              WtPt = cmsReadTag(hProfile, cmsSigMediaWhitePointTag);
              ShowWhitePoint(WtPt);
              cmsCloseProfile(hProfile);
       }
       
       return 0;
}