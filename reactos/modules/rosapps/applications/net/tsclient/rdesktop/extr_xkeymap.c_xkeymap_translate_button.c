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
typedef  int /*<<< orphan*/  uint16 ;

/* Variables and functions */
#define  Button1 132 
#define  Button2 131 
#define  Button3 130 
#define  Button4 129 
#define  Button5 128 
 int /*<<< orphan*/  MOUSE_FLAG_BUTTON1 ; 
 int /*<<< orphan*/  MOUSE_FLAG_BUTTON2 ; 
 int /*<<< orphan*/  MOUSE_FLAG_BUTTON3 ; 
 int /*<<< orphan*/  MOUSE_FLAG_BUTTON4 ; 
 int /*<<< orphan*/  MOUSE_FLAG_BUTTON5 ; 

uint16
xkeymap_translate_button(unsigned int button)
{
	switch (button)
	{
		case Button1:	/* left */
			return MOUSE_FLAG_BUTTON1;
		case Button2:	/* middle */
			return MOUSE_FLAG_BUTTON3;
		case Button3:	/* right */
			return MOUSE_FLAG_BUTTON2;
		case Button4:	/* wheel up */
			return MOUSE_FLAG_BUTTON4;
		case Button5:	/* wheel down */
			return MOUSE_FLAG_BUTTON5;
	}

	return 0;
}