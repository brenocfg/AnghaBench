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
 int ExUtilGetInt (char const*,int,int*) ; 
 char* strchr (char const*,char) ; 

int ExUtilGetInts(const char* v, int base, int max_output, int output[]) {
  int n, error = 0;
  for (n = 0; v != NULL && n < max_output; ++n) {
    const int value = ExUtilGetInt(v, base, &error);
    if (error) return -1;
    output[n] = value;
    v = strchr(v, ',');
    if (v != NULL) ++v;   // skip over the trailing ','
  }
  return n;
}