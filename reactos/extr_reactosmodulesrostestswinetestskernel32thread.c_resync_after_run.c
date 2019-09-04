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
typedef  int LONG ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  num_synced ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  start_event ; 
 int /*<<< orphan*/  stop_event ; 

__attribute__((used)) static void resync_after_run(void)
{
  LONG num = InterlockedDecrement(&num_synced);
  assert(-1 <= num && num <= 1);
  if (num == -1)
  {
      ResetEvent( start_event );
      SetEvent( stop_event );
  }
  else
  {
    DWORD ret = WaitForSingleObject(stop_event, 10000);
    ok(ret == WAIT_OBJECT_0, "WaitForSingleObject failed\n");
  }
}