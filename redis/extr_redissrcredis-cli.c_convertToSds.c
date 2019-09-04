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
 char* sdsnew (char*) ; 
 char** zmalloc (int) ; 

__attribute__((used)) static char **convertToSds(int count, char** args) {
  int j;
  char **sds = zmalloc(sizeof(char*)*count);

  for(j = 0; j < count; j++)
    sds[j] = sdsnew(args[j]);

  return sds;
}