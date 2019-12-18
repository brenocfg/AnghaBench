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
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 char const* strstr (char const*,char const*) ; 

__attribute__((used)) static boolean_t
libzfs_path_contains(const char *path1, const char *path2)
{
	return (strcmp(path1, path2) == 0 || strcmp(path1, "/") == 0 ||
	    (strstr(path2, path1) == path2 && path2[strlen(path1)] == '/'));
}