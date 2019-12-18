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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int BPS ; 
 int /*<<< orphan*/  Put16 (int,scalar_t__*) ; 

__attribute__((used)) static void DC16NoLeft_C(uint8_t* dst) {  // DC with left samples not available
  int DC = 8;
  int i;
  for (i = 0; i < 16; ++i) {
    DC += dst[i - BPS];
  }
  Put16(DC >> 4, dst);
}