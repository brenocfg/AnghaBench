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
typedef  int /*<<< orphan*/  intf_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  HandleKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Redraw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

__attribute__((used)) static void *Run(void *data)
{
    intf_thread_t *intf = data;

    for (;;) {
        vlc_testcancel();

        int canc = vlc_savecancel();

        Redraw(intf);
        HandleKey(intf);
        vlc_restorecancel(canc);
    }
    vlc_assert_unreachable();
}