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
struct atpic {int rotate; int service; int lowprio; } ;

/* Variables and functions */
 int OCW2_EOI ; 
 int OCW2_R ; 
 int OCW2_SL ; 
 int /*<<< orphan*/  VATPIC_CTR1 (struct vatpic*,char*,int) ; 
 int vatpic_get_highest_isrpin (struct atpic*) ; 

__attribute__((used)) static int
vatpic_ocw2(struct vatpic *vatpic, struct atpic *atpic, uint8_t val)
{
	VATPIC_CTR1(vatpic, "atpic ocw2 0x%x", val);

	atpic->rotate = ((val & OCW2_R) != 0);

	if ((val & OCW2_EOI) != 0) {
		int isr_bit;

		if ((val & OCW2_SL) != 0) {
			/* specific EOI */
			isr_bit = val & 0x7;
		} else {
			/* non-specific EOI */
			isr_bit = vatpic_get_highest_isrpin(atpic);
		}

		if (isr_bit != -1) {
			atpic->service &= ~(1 << isr_bit);

			if (atpic->rotate)
				atpic->lowprio = isr_bit;
		}
	} else if ((val & OCW2_SL) != 0 && atpic->rotate == true) {
		/* specific priority */
		atpic->lowprio = val & 0x7;
	}

	return (0);
}