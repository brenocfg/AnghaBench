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
typedef  int BOOL ;

/* Variables and functions */
 int InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  num_synced ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  start_event ; 
 int /*<<< orphan*/  stop_event ; 

__attribute__((used)) static BOOL sync_threads_and_run_one(DWORD sync_id, DWORD my_id)
{
  LONG num = InterlockedIncrement(&num_synced);
  assert(-1 <= num && num <= 1);
  if (num == 1)
  {
      ResetEvent( stop_event );
      SetEvent( start_event );
  }
  else
  {
    DWORD ret = WaitForSingleObject(start_event, 10000);
    ok(ret == WAIT_OBJECT_0, "WaitForSingleObject failed %x\n",ret);
  }
  return sync_id == my_id;
}