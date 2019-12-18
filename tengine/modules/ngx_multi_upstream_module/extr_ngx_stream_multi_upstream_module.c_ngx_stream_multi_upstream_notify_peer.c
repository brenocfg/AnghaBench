#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* original_notify_peer ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ngx_stream_multi_upstream_peer_data_t ;
typedef  int /*<<< orphan*/  ngx_peer_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_stream_multi_upstream_notify_peer(ngx_peer_connection_t *pc,
    void *data, ngx_uint_t type)
{
    ngx_stream_multi_upstream_peer_data_t   *kp = data;

    if (kp->original_notify_peer) {
        kp->original_notify_peer(pc, kp->data, type);
    }
}