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

__attribute__((used)) static const char *paper_size_name(int w, int h)
{
	/* ISO A */
	if (w == 2384 && h == 3370) return "A0";
	if (w == 1684 && h == 2384) return "A1";
	if (w == 1191 && h == 1684) return "A2";
	if (w == 842 && h == 1191) return "A3";
	if (w == 595 && h == 842) return "A4";
	if (w == 420 && h == 595) return "A5";
	if (w == 297 && h == 420) return "A6";

	/* US */
	if (w == 612 && h == 792) return "Letter";
	if (w == 612 && h == 1008) return "Legal";
	if (w == 792 && h == 1224) return "Ledger";
	if (w == 1224 && h == 792) return "Tabloid";

	return NULL;
}