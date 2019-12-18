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
struct instance {scalar_t__ mbuf_chunk_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ MBUF_HSIZE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mbufq ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mbuf_chunk_size ; 
 scalar_t__ mbuf_offset ; 
 scalar_t__ nfree_mbufq ; 

void
mbuf_init(struct instance *nci)
{
    nfree_mbufq = 0;
    STAILQ_INIT(&free_mbufq);

    mbuf_chunk_size = nci->mbuf_chunk_size;
    mbuf_offset = mbuf_chunk_size - MBUF_HSIZE;

    log_debug(LOG_DEBUG, "mbuf hsize %d chunk size %zu offset %zu length %zu",
              MBUF_HSIZE, mbuf_chunk_size, mbuf_offset, mbuf_offset);
}