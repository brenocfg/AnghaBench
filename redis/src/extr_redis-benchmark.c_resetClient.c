#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* client ;
typedef  int /*<<< orphan*/  aeEventLoop ;
struct TYPE_9__ {int /*<<< orphan*/  pipeline; } ;
struct TYPE_8__ {int /*<<< orphan*/  pending; scalar_t__ written; TYPE_1__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 int /*<<< orphan*/  AE_WRITABLE ; 
 int /*<<< orphan*/ * CLIENT_GET_EVENTLOOP (TYPE_2__*) ; 
 int /*<<< orphan*/  aeCreateFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  aeDeleteFileEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ config ; 
 int /*<<< orphan*/  writeHandler ; 

__attribute__((used)) static void resetClient(client c) {
    aeEventLoop *el = CLIENT_GET_EVENTLOOP(c);
    aeDeleteFileEvent(el,c->context->fd,AE_WRITABLE);
    aeDeleteFileEvent(el,c->context->fd,AE_READABLE);
    aeCreateFileEvent(el,c->context->fd,AE_WRITABLE,writeHandler,c);
    c->written = 0;
    c->pending = config.pipeline;
}