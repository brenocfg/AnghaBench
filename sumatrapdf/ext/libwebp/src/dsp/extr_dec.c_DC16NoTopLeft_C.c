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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  Put16 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DC16NoTopLeft_C(uint8_t* dst) {  // DC with no top and left samples
  Put16(0x80, dst);
}