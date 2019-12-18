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
 int EOF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 void* TRUE ; 
 void* lShowLCh ; 
 void* lShowLab ; 
 int /*<<< orphan*/  lShowXYZ ; 
 int xgetopt (int,char**,char*) ; 

__attribute__((used)) static
void HandleSwitches(int argc, char *argv[])
{
       int s;

       while ((s = xgetopt(argc, argv, "lcx")) != EOF) {

              switch (s){


              case 'l':
                     lShowLab = TRUE;
                     break;

              case 'c':
                     lShowLCh = TRUE;
                     break;

              case 'x':
                     lShowXYZ = FALSE;
                     break;

              default:

                     FatalError("Unknown option - run without args to see valid ones.\n");
              }
       }
}