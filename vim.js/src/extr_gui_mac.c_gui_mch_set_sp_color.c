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
typedef  int /*<<< orphan*/  guicolor_T ;
struct TYPE_2__ {int red; int green; int blue; } ;

/* Variables and functions */
 int Blue (int /*<<< orphan*/ ) ; 
 int Green (int /*<<< orphan*/ ) ; 
 int Red (int /*<<< orphan*/ ) ; 
 TYPE_1__ specialColor ; 

void
gui_mch_set_sp_color(guicolor_T color)
{
    specialColor.red = Red(color) * 0x0101;
    specialColor.green = Green(color) * 0x0101;
    specialColor.blue = Blue(color) * 0x0101;
}