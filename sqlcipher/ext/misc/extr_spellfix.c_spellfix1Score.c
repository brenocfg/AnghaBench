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

__attribute__((used)) static int spellfix1Score(int iDistance, int iRank){
  int iLog2;
  for(iLog2=0; iRank>0; iLog2++, iRank>>=1){}
  return iDistance + 32 - iLog2;
}