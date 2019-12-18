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
struct TYPE_3__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_1__ vout_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (uintptr_t) ; 
 int /*<<< orphan*/  free (uintptr_t*) ; 
 int /*<<< orphan*/  serializer ; 
 uintptr_t* used ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vout_window_t *wnd)
{
    uintptr_t val = (uintptr_t)wnd->sys;
    size_t n = 0;

    /* Remove this drawable from the list of busy ones */
    vlc_mutex_lock (&serializer);
    assert (used != NULL);
    while (used[n] != val)
    {
        assert (used[n]);
        n++;
    }
    do
        used[n] = used[n + 1];
    while (used[++n] != 0);

    if (n == 0)
    {
         free (used);
         used = NULL;
    }
    vlc_mutex_unlock (&serializer);
}