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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct msg {int /*<<< orphan*/  mhdr; int /*<<< orphan*/  mlen; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 int /*<<< orphan*/  STAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_copy (struct mbuf*,int /*<<< orphan*/ *,size_t) ; 
 struct mbuf* mbuf_get () ; 
 size_t mbuf_size (struct mbuf*) ; 
 int /*<<< orphan*/  next ; 

rstatus_t
msg_prepend(struct msg *msg, uint8_t *pos, size_t n)
{
    struct mbuf *mbuf;

    mbuf = mbuf_get();
    if (mbuf == NULL) {
        return NC_ENOMEM;
    }

    ASSERT(n <= mbuf_size(mbuf));

    mbuf_copy(mbuf, pos, n);
    msg->mlen += (uint32_t)n;

    STAILQ_INSERT_HEAD(&msg->mhdr, mbuf, next);

    return NC_OK;
}