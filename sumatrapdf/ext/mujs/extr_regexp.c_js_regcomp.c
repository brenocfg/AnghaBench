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
typedef  int /*<<< orphan*/  Reprog ;

/* Variables and functions */
 int /*<<< orphan*/  default_alloc ; 
 int /*<<< orphan*/ * regcompx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int,char const**) ; 

Reprog *regcomp(const char *pattern, int cflags, const char **errorp)
{
	return regcompx(default_alloc, NULL, pattern, cflags, errorp);
}