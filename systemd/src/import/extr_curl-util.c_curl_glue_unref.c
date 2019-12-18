#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_6__ {int /*<<< orphan*/  event; int /*<<< orphan*/ * timer; int /*<<< orphan*/  ios; scalar_t__ curl; } ;
typedef  TYPE_1__ CurlGlue ;

/* Variables and functions */
 int /*<<< orphan*/  curl_multi_cleanup (scalar_t__) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hashmap_steal_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 

CurlGlue *curl_glue_unref(CurlGlue *g) {
        sd_event_source *io;

        if (!g)
                return NULL;

        if (g->curl)
                curl_multi_cleanup(g->curl);

        while ((io = hashmap_steal_first(g->ios))) {
                sd_event_source_unref(io);
        }

        hashmap_free(g->ios);

        sd_event_source_unref(g->timer);
        sd_event_unref(g->event);
        return mfree(g);
}