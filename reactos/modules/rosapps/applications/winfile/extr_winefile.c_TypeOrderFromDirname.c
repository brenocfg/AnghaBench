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
typedef  char* LPCWSTR ;

/* Variables and functions */
 int TO_DOT ; 
 int TO_DOTDOT ; 
 int TO_OTHER_DIR ; 

__attribute__((used)) static int TypeOrderFromDirname(LPCWSTR name)
{
	if (name[0] == '.') {
		if (name[1] == '\0')
			return TO_DOT;	/* "." */

		if (name[1]=='.' && name[2]=='\0')
			return TO_DOTDOT;	/* ".." */
	}

	return TO_OTHER_DIR;	/* anything else */
}