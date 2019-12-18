#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {size_t nelts; TYPE_7__* elts; } ;
struct TYPE_16__ {TYPE_1__ peers; } ;
typedef  TYPE_6__ ngx_http_upstream_check_peers_t ;
struct TYPE_17__ {TYPE_5__* conf; TYPE_3__* shm; TYPE_2__* peer_addr; int /*<<< orphan*/  upstream_name; scalar_t__ delete; } ;
typedef  TYPE_7__ ngx_http_upstream_check_peer_t ;
struct TYPE_18__ {void* last; void* end; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_15__ {int /*<<< orphan*/  port; TYPE_4__* check_type_conf; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  fall_count; int /*<<< orphan*/  rise_count; scalar_t__ down; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 size_t NGX_CHECK_STATUS_DOWN ; 
 size_t NGX_CHECK_STATUS_UP ; 
 int /*<<< orphan*/  ngx_http_upstream_check_shm_generation ; 
 void* ngx_snprintf (void*,void*,char*,...) ; 

__attribute__((used)) static void
ngx_http_upstream_check_status_html_format(ngx_buf_t *b,
    ngx_http_upstream_check_peers_t *peers, ngx_uint_t flag)
{
    ngx_uint_t                      i, count;
    ngx_http_upstream_check_peer_t *peer;

    peer = peers->peers.elts;

    count = 0;

    /* TODO: two locks */
    for (i = 0; i < peers->peers.nelts; i++) {

        if (peer[i].delete) {
            continue;
        }

        if (flag & NGX_CHECK_STATUS_DOWN) {

            if (!peer[i].shm->down) {
                continue;
            }

        } else if (flag & NGX_CHECK_STATUS_UP) {

            if (peer[i].shm->down) {
                continue;
            }
        }

        count++;
    }

    b->last = ngx_snprintf(b->last, b->end - b->last,
            "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\n"
            "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
            "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
            "<head>\n"
            "  <title>Nginx http upstream check status</title>\n"
            "</head>\n"
            "<body>\n"
            "<h1>Nginx http upstream check status</h1>\n"
            "<h2>Check upstream server number: %ui, generation: %ui</h2>\n"
            "<table style=\"background-color:white\" cellspacing=\"0\" "
            "       cellpadding=\"3\" border=\"1\">\n"
            "  <tr bgcolor=\"#C0C0C0\">\n"
            "    <th>Index</th>\n"
            "    <th>Upstream</th>\n"
            "    <th>Name</th>\n"
            "    <th>Status</th>\n"
            "    <th>Rise counts</th>\n"
            "    <th>Fall counts</th>\n"
            "    <th>Check type</th>\n"
            "    <th>Check port</th>\n"
            "  </tr>\n",
            count, ngx_http_upstream_check_shm_generation);

    for (i = 0; i < peers->peers.nelts; i++) {

        if (peer[i].delete) {
            continue;
        }

        if (flag & NGX_CHECK_STATUS_DOWN) {

            if (!peer[i].shm->down) {
                continue;
            }

        } else if (flag & NGX_CHECK_STATUS_UP) {

            if (peer[i].shm->down) {
                continue;
            }
        }

        b->last = ngx_snprintf(b->last, b->end - b->last,
                "  <tr%s>\n"
                "    <td>%ui</td>\n"
                "    <td>%V</td>\n"
                "    <td>%V</td>\n"
                "    <td>%s</td>\n"
                "    <td>%ui</td>\n"
                "    <td>%ui</td>\n"
                "    <td>%V</td>\n"
                "    <td>%ui</td>\n"
                "  </tr>\n",
                peer[i].shm->down ? " bgcolor=\"#FF0000\"" : "",
                i,
                peer[i].upstream_name,
                &peer[i].peer_addr->name,
                peer[i].shm->down ? "down" : "up",
                peer[i].shm->rise_count,
                peer[i].shm->fall_count,
                &peer[i].conf->check_type_conf->name,
                peer[i].conf->port);
    }

    b->last = ngx_snprintf(b->last, b->end - b->last,
            "</table>\n"
            "</body>\n"
            "</html>\n");
}