#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  available; } ;
struct TYPE_10__ {TYPE_1__ space; } ;
struct TYPE_9__ {TYPE_3__ runtime_storage; TYPE_3__ system_storage; scalar_t__ system_journal; } ;
typedef  TYPE_2__ Server ;
typedef  TYPE_3__ JournalStorage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int cache_space_refresh (TYPE_2__*,TYPE_3__*) ; 

__attribute__((used)) static int determine_space(Server *s, uint64_t *available, uint64_t *limit) {
        JournalStorage *js;
        int r;

        assert(s);

        js = s->system_journal ? &s->system_storage : &s->runtime_storage;

        r = cache_space_refresh(s, js);
        if (r >= 0) {
                if (available)
                        *available = js->space.available;
                if (limit)
                        *limit = js->space.limit;
        }
        return r;
}