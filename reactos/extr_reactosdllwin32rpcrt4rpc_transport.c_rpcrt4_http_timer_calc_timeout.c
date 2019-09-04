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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetTickCount () ; 
 scalar_t__ HTTP_IDLE_TIME ; 

__attribute__((used)) static inline DWORD rpcrt4_http_timer_calc_timeout(DWORD *last_sent_time)
{
    DWORD cur_time = GetTickCount();
    DWORD cached_last_sent_time = *last_sent_time;
    return HTTP_IDLE_TIME - (cur_time - cached_last_sent_time > HTTP_IDLE_TIME ? 0 : cur_time - cached_last_sent_time);
}