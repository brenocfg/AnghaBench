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
typedef  unsigned long long vlc_tick_t ;
typedef  unsigned long long libvlc_time_t ;

/* Variables and functions */

__attribute__((used)) static inline libvlc_time_t from_mtime(vlc_tick_t time)
{
    return (time + 500ULL)/ 1000ULL;
}