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

__attribute__((used)) static int tclvarAddToIdxstr(char *zStr, char x){
  int i;
  for(i=0; zStr[i]; i++){
    if( zStr[i]==x ) return 1;
  }
  zStr[i] = x;
  zStr[i+1] = '\0';
  return 0;
}