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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  BRUSH ;

/* Variables and functions */

void ui_ellipse(uint8 opcode, uint8 fillmode,
                int x, int y, int cx, int cy,
                BRUSH * brush, int bgcolour, int fgcolour)
{
}