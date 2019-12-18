#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__** positions; int /*<<< orphan*/  position_count; } ;
struct TYPE_9__ {unsigned int vtnr; unsigned int position; } ;
typedef  TYPE_1__ Session ;
typedef  TYPE_2__ Seat ;

/* Variables and functions */
 int /*<<< orphan*/  GREEDY_REALLOC0 (TYPE_1__**,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  seat_evict_position (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ seat_has_vts (TYPE_2__*) ; 

void seat_claim_position(Seat *s, Session *session, unsigned pos) {
        /* with VTs, the position is always the same as the VTnr */
        if (seat_has_vts(s))
                pos = session->vtnr;

        if (!GREEDY_REALLOC0(s->positions, s->position_count, pos + 1))
                return;

        seat_evict_position(s, session);

        session->position = pos;
        if (pos > 0)
                s->positions[pos] = session;
}