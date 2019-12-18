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

/* Variables and functions */
 int /*<<< orphan*/  Done () ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int /*<<< orphan*/  Help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  OpenInput (char*) ; 
 int /*<<< orphan*/  OpenOutput (char*) ; 
 int /*<<< orphan*/  TransformImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/  cInpProf ; 
 int /*<<< orphan*/  cOutProf ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int xoptind ; 

int main(int argc, char* argv[])
{
    InitUtils(NULL, "jpgicc");

    HandleSwitches(argc, argv);

    if ((argc - xoptind) != 2) {
        Help(0);
    }

    OpenInput(argv[xoptind]);
    OpenOutput(argv[xoptind+1]);

    TransformImage(cInpProf, cOutProf);


    if (Verbose) { fprintf(stdout, "\n"); fflush(stdout); }

    Done();

    return 0;
}