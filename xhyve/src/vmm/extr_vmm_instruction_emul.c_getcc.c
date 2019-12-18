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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  getcc16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getcc64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  getcc8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long
getcc(int opsize, uint64_t x, uint64_t y)
{
	KASSERT(opsize == 1 || opsize == 2 || opsize == 4 || opsize == 8,
	    ("getcc: invalid operand size %d", opsize));

	if (opsize == 1)
		return (getcc8(((uint8_t) x), ((uint8_t) y)));
	else if (opsize == 2)
		return (getcc16(((uint16_t) x), ((uint16_t) y)));
	else if (opsize == 4)
		return (getcc32(((uint32_t) x), ((uint32_t) y)));
	else
		return (getcc64(x, y));
}