#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; void* data; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_ABANDONED_0 ; 
 scalar_t__ WAIT_FAILED ; 
 scalar_t__ WAIT_IO_COMPLETION ; 
 scalar_t__ WaitForSingleObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 
 int /*<<< orphan*/  vlc_thread_destroy (TYPE_1__*) ; 

void vlc_join (vlc_thread_t th, void **result)
{
    DWORD ret;

    do
    {
        vlc_testcancel ();
        ret = WaitForSingleObjectEx(th->id, INFINITE, TRUE);
        assert(ret != WAIT_ABANDONED_0);
    }
    while (ret == WAIT_IO_COMPLETION || ret == WAIT_FAILED);

    if (result != NULL)
        *result = th->data;
    CloseHandle (th->id);
    vlc_thread_destroy(th);
}