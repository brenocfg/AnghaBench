#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int iRand; } ;
typedef  TYPE_1__ testpcache ;

/* Variables and functions */

__attribute__((used)) static unsigned testpcacheRandom(testpcache *p){
  unsigned x = 0;
  int i;
  for(i=0; i<4; i++){
    p->iRand = (p->iRand*69069 + 5);
    x = (x<<8) | ((p->iRand>>16)&0xff);
  }
  return x;
}