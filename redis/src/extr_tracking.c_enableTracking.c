#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  rax ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  client_tracking_redirection; } ;
typedef  TYPE_1__ client ;
struct TYPE_5__ {int /*<<< orphan*/  tracking_clients; } ;

/* Variables and functions */
 int CLIENT_TRACKING ; 
 int CLIENT_TRACKING_BROKEN_REDIR ; 
 int TRACKING_TABLE_SIZE ; 
 int /*<<< orphan*/  TrackingChannelName ; 
 int /*<<< orphan*/ * TrackingTable ; 
 int /*<<< orphan*/  createStringObject (char*,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/ * zcalloc (int) ; 

void enableTracking(client *c, uint64_t redirect_to) {
    if (c->flags & CLIENT_TRACKING) return;
    c->flags |= CLIENT_TRACKING;
    c->flags &= ~CLIENT_TRACKING_BROKEN_REDIR;
    c->client_tracking_redirection = redirect_to;
    server.tracking_clients++;
    if (TrackingTable == NULL) {
        TrackingTable = zcalloc(sizeof(rax*) * TRACKING_TABLE_SIZE);
        TrackingChannelName = createStringObject("__redis__:invalidate",20);
    }
}