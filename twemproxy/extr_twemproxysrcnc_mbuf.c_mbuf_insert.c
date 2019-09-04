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
struct mhdr {int dummy; } ;
struct mbuf {scalar_t__ pos; scalar_t__ last; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct mhdr*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  next ; 

void
mbuf_insert(struct mhdr *mhdr, struct mbuf *mbuf)
{
    STAILQ_INSERT_TAIL(mhdr, mbuf, next);
    log_debug(LOG_VVERB, "insert mbuf %p len %d", mbuf, mbuf->last - mbuf->pos);
}