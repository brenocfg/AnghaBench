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
struct server {int dummy; } ;
struct msg {int /*<<< orphan*/  mlen; int /*<<< orphan*/  request; } ;
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_bytes ; 
 int /*<<< orphan*/  requests ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,struct server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_server_incr_by (struct context*,struct server*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
req_forward_stats(struct context *ctx, struct server *server, struct msg *msg)
{
    ASSERT(msg->request);

    stats_server_incr(ctx, server, requests);
    stats_server_incr_by(ctx, server, request_bytes, msg->mlen);
}