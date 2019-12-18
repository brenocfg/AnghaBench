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

const char* luaT_classrootname(const char *tname)
{
  int idx;
  int sz = strlen(tname);

  for(idx = sz-1; idx >= 0 ; idx--)
  {
    if(tname[idx] == '.')
      return tname+idx+1;
  }
  return tname;
}