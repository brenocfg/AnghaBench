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
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
__strdup(const char *str, int flags)
{
	char *ptr;
	int n;

	n = strlen(str);
	ptr = kmalloc(n + 1, kmem_flags_convert(flags));
	if (ptr)
		memcpy(ptr, str, n + 1);

	return (ptr);
}