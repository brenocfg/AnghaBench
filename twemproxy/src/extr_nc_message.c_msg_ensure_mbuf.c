#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msg {int /*<<< orphan*/  mhdr; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct mbuf* STAILQ_LAST (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* mbuf_get () ; 
 int /*<<< orphan*/  mbuf_insert (int /*<<< orphan*/ *,struct mbuf*) ; 
 size_t mbuf_size (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 

struct mbuf *
msg_ensure_mbuf(struct msg *msg, size_t len)
{
    struct mbuf *mbuf;

    if (STAILQ_EMPTY(&msg->mhdr) ||
        mbuf_size(STAILQ_LAST(&msg->mhdr, mbuf, next)) < len) {
        mbuf = mbuf_get();
        if (mbuf == NULL) {
            return NULL;
        }
        mbuf_insert(&msg->mhdr, mbuf);
    } else {
        mbuf = STAILQ_LAST(&msg->mhdr, mbuf, next);
    }

    return mbuf;
}