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
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int luaT_fullparentname(const char *tname, char *parent_name)
{
  int sz = strlen(tname);
  int idx;
  for(idx = sz-1; idx > 0 ; idx--)
    if(tname[idx] == '.' || tname[idx] == '\0') break;

  if (idx > 0) strncpy(parent_name, tname, idx);
  parent_name[idx] = '\0';
  return tname[idx] == '.';
}