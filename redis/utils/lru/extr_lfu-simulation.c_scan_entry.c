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
typedef  int uint8_t ;
struct entry {int counter; int /*<<< orphan*/  decrtime; } ;

/* Variables and functions */
 int COUNTER_INIT_VAL ; 
 scalar_t__ decr_every ; 
 scalar_t__ minutes_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_16bit_minutes (int /*<<< orphan*/ ) ; 

uint8_t scan_entry(struct entry *e) {
    if (minutes_diff(to_16bit_minutes(time(NULL)),e->decrtime)
        >= decr_every)
    {
        if (e->counter) {
            if (e->counter > COUNTER_INIT_VAL*2) {
                e->counter /= 2;
            } else {
                e->counter--;
            }
        }
        e->decrtime = to_16bit_minutes(time(NULL));
    }
    return e->counter;
}