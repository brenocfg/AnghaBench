#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_9__ {int total_weight; int number; } ;
typedef  TYPE_3__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_10__ {TYPE_1__* conf; } ;
typedef  TYPE_4__ ngx_stream_upstream_random_peer_data_t ;
struct TYPE_8__ {int range; } ;
struct TYPE_7__ {TYPE_2__* ranges; } ;

/* Variables and functions */
 int ngx_random () ; 

__attribute__((used)) static ngx_uint_t
ngx_stream_upstream_peek_random_peer(ngx_stream_upstream_rr_peers_t *peers,
    ngx_stream_upstream_random_peer_data_t *rp)
{
    ngx_uint_t  i, j, k, x;

    x = ngx_random() % peers->total_weight;

    i = 0;
    j = peers->number;

    while (j - i > 1) {
        k = (i + j) / 2;

        if (x < rp->conf->ranges[k].range) {
            j = k;

        } else {
            i = k;
        }
    }

    return i;
}