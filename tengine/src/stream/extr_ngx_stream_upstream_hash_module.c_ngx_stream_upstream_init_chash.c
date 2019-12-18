#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_18__ {TYPE_3__* data; int /*<<< orphan*/  init; } ;
struct TYPE_19__ {TYPE_1__ peer; } ;
typedef  TYPE_2__ ngx_stream_upstream_srv_conf_t ;
struct TYPE_20__ {int total_weight; TYPE_4__* peer; } ;
typedef  TYPE_3__ ngx_stream_upstream_rr_peers_t ;
struct TYPE_24__ {int len; char* data; } ;
struct TYPE_21__ {int weight; TYPE_7__ server; struct TYPE_21__* next; } ;
typedef  TYPE_4__ ngx_stream_upstream_rr_peer_t ;
struct TYPE_22__ {TYPE_6__* points; } ;
typedef  TYPE_5__ ngx_stream_upstream_hash_srv_conf_t ;
struct TYPE_23__ {size_t number; TYPE_15__* point; } ;
typedef  TYPE_6__ ngx_stream_upstream_chash_points_t ;
typedef  int /*<<< orphan*/  ngx_stream_upstream_chash_point_t ;
typedef  TYPE_7__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_25__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_8__ ngx_conf_t ;
struct TYPE_17__ {int hash; TYPE_7__* server; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_crc32_final (int) ; 
 int /*<<< orphan*/  ngx_crc32_init (int) ; 
 int /*<<< orphan*/  ngx_crc32_update (int*,char*,int) ; 
 TYPE_6__* ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_qsort (TYPE_15__*,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_stream_conf_upstream_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_upstream_chash_cmp_points ; 
 int /*<<< orphan*/  ngx_stream_upstream_hash_module ; 
 int /*<<< orphan*/  ngx_stream_upstream_init_chash_peer ; 
 scalar_t__ ngx_stream_upstream_init_round_robin (TYPE_8__*,TYPE_2__*) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_upstream_init_chash(ngx_conf_t *cf,
    ngx_stream_upstream_srv_conf_t *us)
{
    u_char                               *host, *port, c;
    size_t                                host_len, port_len, size;
    uint32_t                              hash, base_hash;
    ngx_str_t                            *server;
    ngx_uint_t                            npoints, i, j;
    ngx_stream_upstream_rr_peer_t        *peer;
    ngx_stream_upstream_rr_peers_t       *peers;
    ngx_stream_upstream_chash_points_t   *points;
    ngx_stream_upstream_hash_srv_conf_t  *hcf;
    union {
        uint32_t                          value;
        u_char                            byte[4];
    } prev_hash;

    if (ngx_stream_upstream_init_round_robin(cf, us) != NGX_OK) {
        return NGX_ERROR;
    }

    us->peer.init = ngx_stream_upstream_init_chash_peer;

    peers = us->peer.data;
    npoints = peers->total_weight * 160;

    size = sizeof(ngx_stream_upstream_chash_points_t)
           + sizeof(ngx_stream_upstream_chash_point_t) * (npoints - 1);

    points = ngx_palloc(cf->pool, size);
    if (points == NULL) {
        return NGX_ERROR;
    }

    points->number = 0;

    for (peer = peers->peer; peer; peer = peer->next) {
        server = &peer->server;

        /*
         * Hash expression is compatible with Cache::Memcached::Fast:
         * crc32(HOST \0 PORT PREV_HASH).
         */

        if (server->len >= 5
            && ngx_strncasecmp(server->data, (u_char *) "unix:", 5) == 0)
        {
            host = server->data + 5;
            host_len = server->len - 5;
            port = NULL;
            port_len = 0;
            goto done;
        }

        for (j = 0; j < server->len; j++) {
            c = server->data[server->len - j - 1];

            if (c == ':') {
                host = server->data;
                host_len = server->len - j - 1;
                port = server->data + server->len - j;
                port_len = j;
                goto done;
            }

            if (c < '0' || c > '9') {
                break;
            }
        }

        host = server->data;
        host_len = server->len;
        port = NULL;
        port_len = 0;

    done:

        ngx_crc32_init(base_hash);
        ngx_crc32_update(&base_hash, host, host_len);
        ngx_crc32_update(&base_hash, (u_char *) "", 1);
        ngx_crc32_update(&base_hash, port, port_len);

        prev_hash.value = 0;
        npoints = peer->weight * 160;

        for (j = 0; j < npoints; j++) {
            hash = base_hash;

            ngx_crc32_update(&hash, prev_hash.byte, 4);
            ngx_crc32_final(hash);

            points->point[points->number].hash = hash;
            points->point[points->number].server = server;
            points->number++;

#if (NGX_HAVE_LITTLE_ENDIAN)
            prev_hash.value = hash;
#else
            prev_hash.byte[0] = (u_char) (hash & 0xff);
            prev_hash.byte[1] = (u_char) ((hash >> 8) & 0xff);
            prev_hash.byte[2] = (u_char) ((hash >> 16) & 0xff);
            prev_hash.byte[3] = (u_char) ((hash >> 24) & 0xff);
#endif
        }
    }

    ngx_qsort(points->point,
              points->number,
              sizeof(ngx_stream_upstream_chash_point_t),
              ngx_stream_upstream_chash_cmp_points);

    for (i = 0, j = 1; j < points->number; j++) {
        if (points->point[i].hash != points->point[j].hash) {
            points->point[++i] = points->point[j];
        }
    }

    points->number = i + 1;

    hcf = ngx_stream_conf_upstream_srv_conf(us,
                                            ngx_stream_upstream_hash_module);
    hcf->points = points;

    return NGX_OK;
}