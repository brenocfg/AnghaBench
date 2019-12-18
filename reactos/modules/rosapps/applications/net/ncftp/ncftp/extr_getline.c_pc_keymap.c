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
#define  K_DELETE 137 
#define  K_DOWN 136 
#define  K_END 135 
#define  K_HOME 134 
#define  K_INSERT 133 
#define  K_LEFT 132 
#define  K_PGDN 131 
#define  K_PGUP 130 
#define  K_RIGHT 129 
#define  K_UP 128 

int pc_keymap(int c)
{
    switch (c) {
	case K_UP:
	case K_PGUP:
		c = 16;		/* up -> ^P */
        break;
	case K_DOWN:
	case K_PGDN:
		c = 14;		/* down -> ^N */
        break;
    case K_LEFT:
		c = 2;		/* left -> ^B */
        break;
    case K_RIGHT:
		c = 6;		/* right -> ^F */
        break;
	case K_END:
		c = 5;		/* end -> ^E */
		break;
	case K_HOME:
		c = 1;		/* home -> ^A */
		break;
	case K_INSERT:
		c = 15;		/* insert -> ^O */
		break;
	case K_DELETE:
		c = 4;		/* del -> ^D */
		break;
    default:
		c = 0;    /* make it garbage */
    }
    return c;
}