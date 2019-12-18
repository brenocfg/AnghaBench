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
 int /*<<< orphan*/  NOCATGETS (char*) ; 
 char* strtok (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workshop_menu_item (char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
process_menuItem(
	char	*cmd)
{
	char *label  = strtok(&cmd[9], NOCATGETS("\001"));
	char *verb  = strtok(NULL, NOCATGETS("\001"));
	char *acc = strtok(NULL, NOCATGETS("\001"));
	char *accText  = strtok(NULL, NOCATGETS("\001"));
	char *name  = strtok(NULL, NOCATGETS("\001"));
	char *sense  = strtok(NULL, NOCATGETS("\n"));
	char *filepos  = strtok(NULL, NOCATGETS("\n"));
	if (*acc == '-') {
		acc = NULL;
	}
	if (*accText == '-') {
		accText = NULL;
	}
	workshop_menu_item(label, verb, acc, accText, name, filepos, sense);

}