#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_4__ {int /*<<< orphan*/  accuracy; int /*<<< orphan*/  next; } ;
struct TYPE_5__ {TYPE_1__ time; } ;
typedef  TYPE_2__ sd_event_source ;

/* Variables and functions */
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t time_event_source_latest(const sd_event_source *s) {
        return usec_add(s->time.next, s->time.accuracy);
}