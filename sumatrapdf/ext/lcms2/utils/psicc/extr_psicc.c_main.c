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
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  GenerateCRD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GenerateCSA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OutFile ; 
 int /*<<< orphan*/ * cInProf ; 
 int /*<<< orphan*/ * cOutProf ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int xoptind ; 

int main(int argc, char *argv[])
{
	int nargs;
    cmsContext ContextID = NULL;

	// Initialize
	InitUtils(NULL, "psicc");

	 HandleSwitches(argc, argv);

     nargs = (argc - xoptind);
	 if (nargs != 0 && nargs != 1)
				Help();

    if (cInProf == NULL && cOutProf == NULL)
        Help();

	 if (nargs == 0)
			OutFile = stdout;
	 else
			OutFile = fopen(argv[xoptind], "wt");

	  if (cInProf != NULL)
			GenerateCSA(ContextID);

	  if (cOutProf != NULL)
			GenerateCRD(ContextID);

	  if (nargs == 1) {
		  fclose(OutFile);
	  }

      return 0;
}