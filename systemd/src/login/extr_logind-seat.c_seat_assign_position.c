#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int position_count; int /*<<< orphan*/ * positions; } ;
struct TYPE_7__ {scalar_t__ position; } ;
typedef  TYPE_1__ Session ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  seat_claim_position (TYPE_2__*,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void seat_assign_position(Seat *s, Session *session) {
        unsigned pos;

        if (session->position > 0)
                return;

        for (pos = 1; pos < s->position_count; ++pos)
                if (!s->positions[pos])
                        break;

        seat_claim_position(s, session, pos);
}