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
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

boolean_t
zfs_prop_written(const char *name)
{
	static const char *prop_prefix = "written@";
	static const char *book_prefix = "written#";
	return (strncmp(name, prop_prefix, strlen(prop_prefix)) == 0 ||
	    strncmp(name, book_prefix, strlen(book_prefix)) == 0);
}