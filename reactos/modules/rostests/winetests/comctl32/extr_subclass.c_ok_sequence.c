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
struct message {scalar_t__ procnum; scalar_t__ wParam; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_message (struct message const*) ; 
 int /*<<< orphan*/  flush_sequence () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 struct message* sequence ; 

__attribute__((used)) static void ok_sequence(const struct message *expected, const char *context)
{
    static const struct message end_of_sequence = { 0, 0 };
    const struct message *actual;

    add_message(&end_of_sequence);

    actual = sequence;

    while(expected->procnum && actual->procnum)
    {
        ok(expected->procnum == actual->procnum,
            "%s: the procnum %d was expected, but got procnum %d instead\n",
            context, expected->procnum, actual->procnum);
        ok(expected->wParam == actual->wParam,
            "%s: in procnum %d expecting wParam 0x%lx got 0x%lx\n",
            context, expected->procnum, expected->wParam, actual->wParam);
        expected++;
        actual++;
    }
    ok(!expected->procnum, "Received fewer messages than expected\n");
    ok(!actual->procnum, "Received more messages than expected\n");
    flush_sequence();
}