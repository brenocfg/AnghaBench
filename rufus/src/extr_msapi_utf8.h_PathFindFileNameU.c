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
 size_t strlen (char const*) ; 

__attribute__((used)) static __inline const char* PathFindFileNameU(const char* szPath)
{
	size_t i;
	if (szPath == NULL)
		return NULL;
	for (i = strlen(szPath); i != 0; i--) {
		if ((szPath[i] == '/') || (szPath[i] == '\\')) {
			i++;
			break;
		}
	}
	return &szPath[i];
}