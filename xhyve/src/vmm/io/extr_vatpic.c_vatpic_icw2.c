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
struct atpic {int irq_base; int /*<<< orphan*/  icw_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  VATPIC_CTR1 (struct vatpic*,char*,int) ; 

__attribute__((used)) static int
vatpic_icw2(struct vatpic *vatpic, struct atpic *atpic, uint8_t val)
{
	VATPIC_CTR1(vatpic, "atpic icw2 0x%x", val);

	atpic->irq_base = val & 0xf8;

	atpic->icw_num++;

	return (0);
}