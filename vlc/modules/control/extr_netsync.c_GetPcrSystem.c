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
typedef  int vlc_tick_t ;
typedef  int /*<<< orphan*/  input_thread_t ;

/* Variables and functions */
 scalar_t__ input_GetPcrSystem (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 

__attribute__((used)) static vlc_tick_t GetPcrSystem(input_thread_t *input)
{
    int canc = vlc_savecancel();
    /* TODO use the delay */
    vlc_tick_t system;
    if (input_GetPcrSystem(input, &system, NULL))
        system = -1;
    vlc_restorecancel(canc);

    return system;
}