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
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void sqlite3Delete83Name(char *z){
  int i, sz;
  sz = (int)strlen(z);
  for(i=sz-1; i>0 && z[i]!='/' && z[i]!='.'; i--){}
  if( z[i]=='.' && (sz>i+4) ) memmove(&z[i+1], &z[sz-3], 4);
}