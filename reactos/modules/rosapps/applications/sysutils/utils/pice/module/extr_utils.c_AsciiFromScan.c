#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
typedef  scalar_t__ UCHAR ;
struct TYPE_4__ {TYPE_1__* normal; TYPE_1__* alted; TYPE_1__* shifted; } ;
struct TYPE_3__ {scalar_t__ s; scalar_t__ a; } ;
typedef  TYPE_1__* PSCANTOASCII ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 TYPE_2__* GetKeyboardLayout () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ bAlt ; 
 scalar_t__ bShift ; 

UCHAR AsciiFromScan(UCHAR s)
{
  PSCANTOASCII table;
  ULONG i;

  ENTER_FUNC();

  if (bShift)
    {
      table = GetKeyboardLayout()->shifted;
    }
  else if(bAlt)
    {
      table = GetKeyboardLayout()->alted;
    }
  else
    {
      table = GetKeyboardLayout()->normal;
    }


  if (table)
    {
	  for(i=0;table[i].s != 0;i++)
	    {
	      if(table[i].s==s)
	        {
			  LEAVE_FUNC();
			  return table[i].a;
	        }
	    }
    }

  DPRINT((0,"AsciiFromScan(): no translation for key\n"));
  LEAVE_FUNC();
  return 0;
}