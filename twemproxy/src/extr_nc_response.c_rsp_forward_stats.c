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
typedef  int /*<<< orphan*/  uint32_t ;
struct server {int dummy; } ;
struct msg {int /*<<< orphan*/  request; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  response_bytes ; 
 int /*<<< orphan*/  responses ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,struct server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_server_incr_by (struct context*,struct server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rsp_forward_stats(struct context *ctx, struct server *server, struct msg *msg, uint32_t msgsize)
{
    ASSERT(!msg->request);

    stats_server_incr(ctx, server, responses);
    stats_server_incr_by(ctx, server, response_bytes, msgsize);
}