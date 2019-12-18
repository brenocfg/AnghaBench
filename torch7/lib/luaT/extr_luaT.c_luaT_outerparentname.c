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
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

int luaT_outerparentname(const char *tname, char *parent_name)
{
  char chars[] = {'.', '\0'};
  size_t idx;
  idx = strcspn(tname, chars);
  strncpy(parent_name, tname, idx);
  parent_name[idx] = '\0';
  return tname[idx] == '.';
}