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
 scalar_t__* UpperToLower ; 

int sqlite3StrICmp(const char *zLeft, const char *zRight){
  unsigned char *a, *b;
  int c;
  a = (unsigned char *)zLeft;
  b = (unsigned char *)zRight;
  for(;;){
    c = (int)UpperToLower[*a] - (int)UpperToLower[*b];
    if( c || *a==0 ) break;
    a++;
    b++;
  }
  return c;
}