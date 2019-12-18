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

int
computeSignal (int exceptionVector)
{
  int sigval;
  switch (exceptionVector)
	{
	case 0:
	  sigval = 8;
	  break;					/* divide by zero */
	case 1:
	  sigval = 5;
	  break;					/* debug exception */
	case 3:
	  sigval = 5;
	  break;					/* breakpoint */
	case 4:
	  sigval = 16;
	  break;					/* into instruction (overflow) */
	case 5:
	  sigval = 16;
	  break;					/* bound instruction */
	case 6:
	  sigval = 4;
	  break;					/* Invalid opcode */
	case 7:
	  sigval = 8;
	  break;					/* coprocessor not available */
	case 8:
	  sigval = 7;
	  break;					/* double fault */
	case 9:
	  sigval = 11;
	  break;					/* coprocessor segment overrun */
	case 10:
	  sigval = 11;
	  break;					/* Invalid TSS */
	case 11:
	  sigval = 11;
	  break;					/* Segment not present */
	case 12:
	  sigval = 11;
	  break;					/* stack exception */
	case 13:
	  sigval = 11;
	  break;					/* general protection */
	case 14:
	  sigval = 11;
	  break;					/* page fault */
	case 16:
	  sigval = 7;
	  break;					/* coprocessor error */
	default:
	  sigval = 7;				/* "software generated" */
	}
  return (sigval);
}