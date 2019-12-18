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
struct context {int dummy; } ;
struct conn {int dummy; } ;

/* Variables and functions */

void
memcache_post_connect(struct context *ctx, struct conn *conn, struct server *server)
{
}