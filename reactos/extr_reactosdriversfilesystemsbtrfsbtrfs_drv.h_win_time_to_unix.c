#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONGLONG ;
typedef  scalar_t__ UINT32 ;
struct TYPE_6__ {int seconds; scalar_t__ nanoseconds; } ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  TYPE_2__ BTRFS_TIME ;

/* Variables and functions */

__attribute__((used)) static __inline void win_time_to_unix(LARGE_INTEGER t, BTRFS_TIME* out) {
    ULONGLONG l = (ULONGLONG)t.QuadPart - 116444736000000000;

    out->seconds = l / 10000000;
    out->nanoseconds = (UINT32)((l % 10000000) * 100);
}