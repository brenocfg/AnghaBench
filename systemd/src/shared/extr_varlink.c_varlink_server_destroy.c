#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* description; int /*<<< orphan*/  event; int /*<<< orphan*/  by_uid; int /*<<< orphan*/  methods; } ;
typedef  TYPE_1__ VarlinkServer ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 char* hashmap_steal_first_key (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varlink_server_shutdown (TYPE_1__*) ; 

__attribute__((used)) static VarlinkServer* varlink_server_destroy(VarlinkServer *s) {
        char *m;

        if (!s)
                return NULL;

        varlink_server_shutdown(s);

        while ((m = hashmap_steal_first_key(s->methods)))
                free(m);

        hashmap_free(s->methods);
        hashmap_free(s->by_uid);

        sd_event_unref(s->event);

        free(s->description);

        return mfree(s);
}