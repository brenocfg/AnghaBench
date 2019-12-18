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
 int /*<<< orphan*/  banner () ; 
 int /*<<< orphan*/  printf (char*) ; 

void showhelp(void)
{
    banner();
    printf("LOADER: Syntax:\n");
    printf("LOADER:         loader [switches] [executable/object file path]\n");
    printf("LOADER: Switches:\n");
    printf("LOADER:         -trans      (-t):   translate from exe to sym\n");
    printf("LOADER:         -load       (-l):   load symbols\n");
    printf("LOADER:         -unload     (-u):   unload symbols\n");
    printf("LOADER:         -reload     (-r):   reload some/all symbols\n");
    printf("LOADER:         -verbose    (-v):   be a bit more verbose\n");
    printf("LOADER:         -install    (-i):   install pICE debugger\n");
    printf("LOADER:         -uninstall  (-x):   uninstall pICE debugger\n");
    printf("LOADER:         -break      (-b):   break into debugger\n");
    printf("LOADER:         -serial     (-ser): start serial line terminal\n");
}