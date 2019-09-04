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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
#define  SCANCODE_CHAR_LALT 136 
#define  SCANCODE_CHAR_LCTRL 135 
#define  SCANCODE_CHAR_LSHIFT 134 
#define  SCANCODE_CHAR_LWIN 133 
#define  SCANCODE_CHAR_NUMLOCK 132 
#define  SCANCODE_CHAR_RALT 131 
#define  SCANCODE_CHAR_RCTRL 130 
#define  SCANCODE_CHAR_RSHIFT 129 
#define  SCANCODE_CHAR_RWIN 128 
 int /*<<< orphan*/  True ; 

__attribute__((used)) static BOOL
is_modifier(uint8 scancode)
{
	switch (scancode)
	{
		case SCANCODE_CHAR_LSHIFT:
		case SCANCODE_CHAR_RSHIFT:
		case SCANCODE_CHAR_LCTRL:
		case SCANCODE_CHAR_RCTRL:
		case SCANCODE_CHAR_LALT:
		case SCANCODE_CHAR_RALT:
		case SCANCODE_CHAR_LWIN:
		case SCANCODE_CHAR_RWIN:
		case SCANCODE_CHAR_NUMLOCK:
			return True;
		default:
			break;
	}
	return False;
}