#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ToxAVCall ;
struct TYPE_3__ {size_t calls_tail; int /*<<< orphan*/ ** calls; } ;
typedef  TYPE_1__ ToxAV ;

/* Variables and functions */

ToxAVCall *call_get(ToxAV *av, uint32_t friend_number)
{
    /* Assumes mutex locked */
    if (av->calls == NULL || av->calls_tail < friend_number)
        return NULL;

    return av->calls[friend_number];
}