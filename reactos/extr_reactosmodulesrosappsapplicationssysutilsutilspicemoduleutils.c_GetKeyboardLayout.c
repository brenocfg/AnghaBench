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
typedef  int /*<<< orphan*/ * PKEYBOARD_LAYOUT ;

/* Variables and functions */
 int /*<<< orphan*/ * CurrentKeyboard ; 
 size_t kbUS ; 
 int /*<<< orphan*/ * ucKeyboard ; 

PKEYBOARD_LAYOUT GetKeyboardLayout()
{
  if (CurrentKeyboard == NULL)
    {
      CurrentKeyboard = &ucKeyboard[kbUS];
    }

  return CurrentKeyboard;
}