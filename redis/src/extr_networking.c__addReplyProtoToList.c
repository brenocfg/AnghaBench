#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_9__ {size_t size; size_t used; scalar_t__ buf; } ;
typedef  TYPE_1__ clientReplyBlock ;
struct TYPE_10__ {int flags; int reply_bytes; int /*<<< orphan*/  reply; } ;
typedef  TYPE_2__ client ;

/* Variables and functions */
 int CLIENT_CLOSE_AFTER_REPLY ; 
 size_t PROTO_REPLY_CHUNK_BYTES ; 
 int /*<<< orphan*/  asyncCloseClientOnOutputBufferLimitReached (TYPE_2__*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * listLast (int /*<<< orphan*/ ) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 
 TYPE_1__* zmalloc (size_t) ; 
 int zmalloc_usable (TYPE_1__*) ; 

void _addReplyProtoToList(client *c, const char *s, size_t len) {
    if (c->flags & CLIENT_CLOSE_AFTER_REPLY) return;

    listNode *ln = listLast(c->reply);
    clientReplyBlock *tail = ln? listNodeValue(ln): NULL;

    /* Note that 'tail' may be NULL even if we have a tail node, becuase when
     * addDeferredMultiBulkLength() is used, it sets a dummy node to NULL just
     * fo fill it later, when the size of the bulk length is set. */

    /* Append to tail string when possible. */
    if (tail) {
        /* Copy the part we can fit into the tail, and leave the rest for a
         * new node */
        size_t avail = tail->size - tail->used;
        size_t copy = avail >= len? len: avail;
        memcpy(tail->buf + tail->used, s, copy);
        tail->used += copy;
        s += copy;
        len -= copy;
    }
    if (len) {
        /* Create a new node, make sure it is allocated to at
         * least PROTO_REPLY_CHUNK_BYTES */
        size_t size = len < PROTO_REPLY_CHUNK_BYTES? PROTO_REPLY_CHUNK_BYTES: len;
        tail = zmalloc(size + sizeof(clientReplyBlock));
        /* take over the allocation's internal fragmentation */
        tail->size = zmalloc_usable(tail) - sizeof(clientReplyBlock);
        tail->used = len;
        memcpy(tail->buf, s, len);
        listAddNodeTail(c->reply, tail);
        c->reply_bytes += tail->size;
    }
    asyncCloseClientOnOutputBufferLimitReached(c);
}