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
struct TYPE_4__ {int /*<<< orphan*/  sessions; } ;
typedef  TYPE_1__ SeatStatusInfo ;

/* Variables and functions */
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero (TYPE_1__) ; 

__attribute__((used)) static void seat_status_info_clear(SeatStatusInfo *info) {
        if (info) {
                strv_free(info->sessions);
                zero(*info);
        }
}