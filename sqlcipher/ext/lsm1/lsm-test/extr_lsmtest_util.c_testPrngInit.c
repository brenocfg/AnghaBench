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
struct TYPE_2__ {scalar_t__ aRand3; scalar_t__ aRand2; scalar_t__ aRand1; } ;

/* Variables and functions */
 TYPE_1__ r ; 
 int /*<<< orphan*/  randomBlob (int,unsigned char*) ; 

int testPrngInit(void){
  randomBlob(sizeof(r.aRand1), (unsigned char *)r.aRand1);
  randomBlob(sizeof(r.aRand2), (unsigned char *)r.aRand2);
  randomBlob(sizeof(r.aRand3), (unsigned char *)r.aRand3);
  return 0;
}