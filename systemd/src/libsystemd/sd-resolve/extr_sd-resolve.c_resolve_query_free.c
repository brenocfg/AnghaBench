#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  serv; int /*<<< orphan*/  host; int /*<<< orphan*/  addrinfo; int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* destroy_callback ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ sd_resolve_query ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  resolve_freeaddrinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_query_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_resolve_query *resolve_query_free(sd_resolve_query *q) {
        assert(q);

        resolve_query_disconnect(q);

        if (q->destroy_callback)
                q->destroy_callback(q->userdata);

        resolve_freeaddrinfo(q->addrinfo);
        free(q->host);
        free(q->serv);

        return mfree(q);
}