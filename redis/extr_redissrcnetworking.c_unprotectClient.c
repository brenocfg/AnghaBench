#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ client ;
struct TYPE_8__ {int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int CLIENT_PROTECTED ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ clientHasPendingReplies (TYPE_1__*) ; 
 int /*<<< orphan*/  clientInstallWriteHandler (TYPE_1__*) ; 
 int /*<<< orphan*/  readQueryFromClient ; 
 TYPE_3__ server ; 

void unprotectClient(client *c) {
    if (c->flags & CLIENT_PROTECTED) {
        c->flags &= ~CLIENT_PROTECTED;
        aeCreateFileEvent(server.el,c->fd,AE_READABLE,readQueryFromClient,c);
        if (clientHasPendingReplies(c)) clientInstallWriteHandler(c);
    }
}