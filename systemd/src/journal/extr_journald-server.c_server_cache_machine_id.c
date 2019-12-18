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
typedef  int /*<<< orphan*/  sd_id128_t ;
struct TYPE_4__ {int /*<<< orphan*/  machine_id_field; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_id128_get_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stpcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void server_cache_machine_id(Server *s) {
        sd_id128_t id;
        int r;

        assert(s);

        r = sd_id128_get_machine(&id);
        if (r < 0)
                return;

        sd_id128_to_string(id, stpcpy(s->machine_id_field, "_MACHINE_ID="));
}