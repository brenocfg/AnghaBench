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

__attribute__((used)) static unsigned int findCloseParen(const char *z){
  unsigned int nOpen = 0;
  unsigned i;
  for(i=0; z[i]; i++){
    if( z[i]=='(' ) nOpen++;
    if( z[i]==')' ){
      if( nOpen==0 ) break;
      nOpen--;
    }
  }
  return i;
}