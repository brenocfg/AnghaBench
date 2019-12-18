#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
typedef  size_t ngx_int_t ;
struct TYPE_13__ {int next; int /*<<< orphan*/  handler; int /*<<< orphan*/  checker; } ;
typedef  TYPE_4__ ngx_http_phase_handler_t ;
typedef  int /*<<< orphan*/  ngx_http_phase_handler_pt ;
typedef  int /*<<< orphan*/  ngx_http_handler_pt ;
struct TYPE_10__ {int server_rewrite_index; int location_rewrite_index; TYPE_4__* handlers; } ;
struct TYPE_14__ {TYPE_3__* phases; TYPE_1__ phase_engine; } ;
typedef  TYPE_5__ ngx_http_core_main_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_11__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
struct TYPE_12__ {TYPE_2__ handlers; } ;

/* Variables and functions */
 size_t NGX_ERROR ; 
#define  NGX_HTTP_ACCESS_PHASE 134 
#define  NGX_HTTP_CONTENT_PHASE 133 
#define  NGX_HTTP_FIND_CONFIG_PHASE 132 
 int NGX_HTTP_LOG_PHASE ; 
#define  NGX_HTTP_POST_ACCESS_PHASE 131 
#define  NGX_HTTP_POST_REWRITE_PHASE 130 
#define  NGX_HTTP_REWRITE_PHASE 129 
#define  NGX_HTTP_SERVER_REWRITE_PHASE 128 
 size_t NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_access_phase ; 
 int /*<<< orphan*/  ngx_http_core_content_phase ; 
 int /*<<< orphan*/  ngx_http_core_find_config_phase ; 
 int /*<<< orphan*/  ngx_http_core_generic_phase ; 
 int /*<<< orphan*/  ngx_http_core_post_access_phase ; 
 int /*<<< orphan*/  ngx_http_core_post_rewrite_phase ; 
 int /*<<< orphan*/  ngx_http_core_rewrite_phase ; 
 TYPE_4__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_init_phase_handlers(ngx_conf_t *cf, ngx_http_core_main_conf_t *cmcf)
{
    ngx_int_t                   j;
    ngx_uint_t                  i, n;
    ngx_uint_t                  find_config_index, use_rewrite, use_access;
    ngx_http_handler_pt        *h;
    ngx_http_phase_handler_t   *ph;
    ngx_http_phase_handler_pt   checker;

    cmcf->phase_engine.server_rewrite_index = (ngx_uint_t) -1;
    cmcf->phase_engine.location_rewrite_index = (ngx_uint_t) -1;
    find_config_index = 0;
    use_rewrite = cmcf->phases[NGX_HTTP_REWRITE_PHASE].handlers.nelts ? 1 : 0;
    use_access = cmcf->phases[NGX_HTTP_ACCESS_PHASE].handlers.nelts ? 1 : 0;

    n = 1                  /* find config phase */
        + use_rewrite      /* post rewrite phase */
        + use_access;      /* post access phase */

    for (i = 0; i < NGX_HTTP_LOG_PHASE; i++) {
        n += cmcf->phases[i].handlers.nelts;
    }

    ph = ngx_pcalloc(cf->pool,
                     n * sizeof(ngx_http_phase_handler_t) + sizeof(void *));
    if (ph == NULL) {
        return NGX_ERROR;
    }

    cmcf->phase_engine.handlers = ph;
    n = 0;

    for (i = 0; i < NGX_HTTP_LOG_PHASE; i++) {
        h = cmcf->phases[i].handlers.elts;

        switch (i) {

        case NGX_HTTP_SERVER_REWRITE_PHASE:
            if (cmcf->phase_engine.server_rewrite_index == (ngx_uint_t) -1) {
                cmcf->phase_engine.server_rewrite_index = n;
            }
            checker = ngx_http_core_rewrite_phase;

            break;

        case NGX_HTTP_FIND_CONFIG_PHASE:
            find_config_index = n;

            ph->checker = ngx_http_core_find_config_phase;
            n++;
            ph++;

            continue;

        case NGX_HTTP_REWRITE_PHASE:
            if (cmcf->phase_engine.location_rewrite_index == (ngx_uint_t) -1) {
                cmcf->phase_engine.location_rewrite_index = n;
            }
            checker = ngx_http_core_rewrite_phase;

            break;

        case NGX_HTTP_POST_REWRITE_PHASE:
            if (use_rewrite) {
                ph->checker = ngx_http_core_post_rewrite_phase;
                ph->next = find_config_index;
                n++;
                ph++;
            }

            continue;

        case NGX_HTTP_ACCESS_PHASE:
            checker = ngx_http_core_access_phase;
            n++;
            break;

        case NGX_HTTP_POST_ACCESS_PHASE:
            if (use_access) {
                ph->checker = ngx_http_core_post_access_phase;
                ph->next = n;
                ph++;
            }

            continue;

        case NGX_HTTP_CONTENT_PHASE:
            checker = ngx_http_core_content_phase;
            break;

        default:
            checker = ngx_http_core_generic_phase;
        }

        n += cmcf->phases[i].handlers.nelts;

        for (j = cmcf->phases[i].handlers.nelts - 1; j >= 0; j--) {
            ph->checker = checker;
            ph->handler = h[j];
            ph->next = n;
            ph++;
        }
    }

    return NGX_OK;
}