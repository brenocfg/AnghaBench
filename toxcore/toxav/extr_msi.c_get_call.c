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
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t calls_tail; int /*<<< orphan*/ ** calls; } ;
typedef  TYPE_1__ MSISession ;
typedef  int /*<<< orphan*/  MSICall ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static MSICall *get_call (MSISession *session, uint32_t friend_number)
{
    assert(session);

    if (session->calls == NULL || session->calls_tail < friend_number)
        return NULL;

    return session->calls[friend_number];
}