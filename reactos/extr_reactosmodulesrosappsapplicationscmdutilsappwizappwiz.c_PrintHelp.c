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
 char* _T (char*) ; 
 int /*<<< orphan*/  _getch () ; 
 int /*<<< orphan*/  printf (char*) ; 

void PrintHelp()
{
	printf(_T("Add or Remove Programs\n\
APPWIZ [/? /l] [/all /app /upd]\n\
  /?\t Help\n\
  /l\t Show list\n\
  /all\t Show programs and updates\n\
  /app\t Show programs only\n\
  /upd\t Show updates only\n"));
    _getch();
}