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
typedef  int uint8_t ;
struct vatpic {int dummy; } ;
struct atpic {int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATPIC_CTR1 (struct vatpic*,char*,int) ; 

__attribute__((used)) static int
vatpic_ocw1(struct vatpic *vatpic, struct atpic *atpic, uint8_t val)
{
	VATPIC_CTR1(vatpic, "atpic ocw1 0x%x", val);

	atpic->mask = val & 0xff;

	return (0);
}