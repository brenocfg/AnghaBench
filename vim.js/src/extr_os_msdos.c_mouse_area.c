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
struct TYPE_2__ {int dx; int ax; scalar_t__ cx; } ;
union REGS {TYPE_1__ x; } ;

/* Variables and functions */
 int Columns ; 
 int Rows ; 
 int /*<<< orphan*/  int86 (int,union REGS*,union REGS*) ; 
 scalar_t__ mouse_avail ; 
 int mouse_x_div ; 
 int mouse_y_div ; 

__attribute__((used)) static void
mouse_area(void)
{
    union REGS	    regs;

    if (mouse_avail)
    {
	regs.x.cx = 0;	/* mouse visible between cx and dx */
	regs.x.dx = Columns * mouse_x_div - 1;
	regs.x.ax = 7;
	(void)int86(0x33, &regs, &regs);

	regs.x.cx = 0;	/* mouse visible between cx and dx */
	regs.x.dx = Rows * mouse_y_div - 1;
	regs.x.ax = 8;
	(void)int86(0x33, &regs, &regs);
    }
}