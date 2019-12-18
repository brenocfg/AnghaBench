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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

BOOL
str_startswith(const char *s, const char *prefix)
{
	return (strncmp(s, prefix, strlen(prefix)) == 0);
}