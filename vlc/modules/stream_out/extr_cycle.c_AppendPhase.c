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
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  chain; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ sout_cycle_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AppendPhase(sout_cycle_t ***restrict pp,
                       vlc_tick_t offset, const char *chain)
{

    size_t len = strlen(chain);
    sout_cycle_t *cycle = malloc(sizeof (*cycle) + len);
    if (unlikely(cycle == NULL))
        return -1;

    cycle->next = NULL;
    cycle->offset = offset;
    memcpy(cycle->chain, chain, len + 1);

    **pp = cycle;
    *pp = &cycle->next;
    return 0;
}