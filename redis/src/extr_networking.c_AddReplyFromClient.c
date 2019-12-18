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
struct TYPE_6__ {scalar_t__ bufpos; scalar_t__ reply_bytes; int /*<<< orphan*/  reply; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ client ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  addReplyProto (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  listJoin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 scalar_t__ prepareClientToWrite (TYPE_1__*) ; 

void AddReplyFromClient(client *dst, client *src) {
    if (prepareClientToWrite(dst) != C_OK)
        return;
    addReplyProto(dst,src->buf, src->bufpos);
    if (listLength(src->reply))
        listJoin(dst->reply,src->reply);
    dst->reply_bytes += src->reply_bytes;
    src->reply_bytes = 0;
    src->bufpos = 0;
}