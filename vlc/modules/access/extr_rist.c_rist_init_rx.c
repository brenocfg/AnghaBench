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
struct rtp_pkt {int dummy; } ;
struct rist_flow {int reset; int fd_in; int fd_nack; int fd_rtcp_m; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int RIST_QUEUE_SIZE ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct rist_flow*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rist_flow *rist_init_rx(void)
{
    struct rist_flow *flow = calloc(1, sizeof(struct rist_flow));
    if (!flow)
        return NULL;

    flow->reset = 1;
    flow->buffer = calloc(RIST_QUEUE_SIZE, sizeof(struct rtp_pkt));

    if ( unlikely( flow->buffer == NULL ) )
    {
        free(flow);
        return NULL;
    }
    flow->fd_in = -1;
    flow->fd_nack = -1;
    flow->fd_rtcp_m = -1;

    return flow;
}