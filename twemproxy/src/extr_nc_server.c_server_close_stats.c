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
typedef  int err_t ;

/* Variables and functions */
#define  ECONNABORTED 137 
#define  ECONNREFUSED 136 
#define  ECONNRESET 135 
#define  EHOSTDOWN 134 
#define  EHOSTUNREACH 133 
#define  ENETDOWN 132 
#define  ENETUNREACH 131 
#define  ENOTCONN 130 
#define  EPIPE 129 
#define  ETIMEDOUT 128 
 int /*<<< orphan*/  server_connections ; 
 int /*<<< orphan*/  server_eof ; 
 int /*<<< orphan*/  server_err ; 
 int /*<<< orphan*/  server_timedout ; 
 int /*<<< orphan*/  stats_server_decr (struct context*,struct server*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,struct server*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
server_close_stats(struct context *ctx, struct server *server, err_t err,
                   unsigned eof, unsigned connected)
{
    if (connected) {
        stats_server_decr(ctx, server, server_connections);
    }

    if (eof) {
        stats_server_incr(ctx, server, server_eof);
        return;
    }

    switch (err) {
    case ETIMEDOUT:
        stats_server_incr(ctx, server, server_timedout);
        break;
    case EPIPE:
    case ECONNRESET:
    case ECONNABORTED:
    case ECONNREFUSED:
    case ENOTCONN:
    case ENETDOWN:
    case ENETUNREACH:
    case EHOSTDOWN:
    case EHOSTUNREACH:
    default:
        stats_server_incr(ctx, server, server_err);
        break;
    }
}