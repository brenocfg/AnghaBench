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

int luaT_innerparentname(const char *tname, char *parent_name)
{
  int sz = strlen(tname);
  int tail, head;
  for(tail = sz-1; tail >= 0 ; tail--) // tail points to
    if(tname[tail] == '.') break;      // just past IPN

  if (tail == 0) return 0;

  for(head = tail-1; head >= 0; head--) // head points to
    if(tname[head] == '.') break;       // just before IPN

  head += 1; // update head to start of IPN
  tail -= head; // update tail to strlen(IPN)
  strncpy(parent_name, tname+head, tail);
  parent_name[tail] = '\0';
  return 1;
}