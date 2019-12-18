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

__attribute__((used)) static const char *fileTail(const char *z){
  int i;
  if( z==0 ) return 0;
  i = strlen(z)-1;
  while( i>0 && z[i-1]!='/' ){ i--; }
  return &z[i];
}