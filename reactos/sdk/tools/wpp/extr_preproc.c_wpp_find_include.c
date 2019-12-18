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
 int /*<<< orphan*/  includepath ; 
 int /*<<< orphan*/  nincludepath ; 
 char* wpp_default_lookup (char const*,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *wpp_find_include(const char *name, const char *parent_name)
{
    return wpp_default_lookup(name, !!parent_name, parent_name, includepath, nincludepath);
}