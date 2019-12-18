#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int* aRand1; unsigned int* aRand2; unsigned int* aRand3; } ;

/* Variables and functions */
 TYPE_1__ r ; 

unsigned int testPrngValue(unsigned int iVal){
  return
    r.aRand1[iVal & 0x000007FF] ^
    r.aRand2[(iVal>>11) & 0x000007FF] ^
    r.aRand3[(iVal>>22) & 0x000003FF]
  ;
}