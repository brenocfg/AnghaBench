#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ message; } ;
typedef  TYPE_1__* LPMSG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WM_DEVICECHANGE ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 

__attribute__((used)) static BOOL spurious_message(LPMSG msg)
{
  /* WM_DEVICECHANGE 0x0219 appears randomly */
  if(msg->message == WM_DEVICECHANGE) {
    trace("skipping spurious message %04x\n", msg->message);
    return TRUE;
  }
  return FALSE;
}