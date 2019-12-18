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

__attribute__((used)) static int numberOfVChar(const char *z){
  int N = 0;
  while( z[0] && z[0]=='v' ){
    z++;
    N++;
  }
  return z[0]==0 ? N : 0;
}