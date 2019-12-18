#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  name; TYPE_1__* regex; } ;
typedef  TYPE_2__ ngx_regex_elt_t ;
struct TYPE_12__ {scalar_t__ pcre_jit; } ;
typedef  TYPE_3__ ngx_regex_conf_t ;
struct TYPE_13__ {TYPE_9__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_4__ ngx_pool_cleanup_t ;
struct TYPE_14__ {size_t nelts; TYPE_2__* elts; struct TYPE_14__* next; } ;
typedef  TYPE_5__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_6__ ngx_cycle_t ;
struct TYPE_16__ {TYPE_5__ part; } ;
struct TYPE_10__ {int /*<<< orphan*/  extra; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  PCRE_INFO_JIT ; 
 int PCRE_STUDY_JIT_COMPILE ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  ngx_pcre_free_studies ; 
 TYPE_9__* ngx_pcre_studies ; 
 TYPE_4__* ngx_pool_cleanup_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_regex_malloc_done () ; 
 int /*<<< orphan*/  ngx_regex_malloc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_regex_module ; 
 int pcre_fullinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcre_study (int /*<<< orphan*/ ,int,char const**) ; 

__attribute__((used)) static ngx_int_t
ngx_regex_module_init(ngx_cycle_t *cycle)
{
    int               opt;
    const char       *errstr;
    ngx_uint_t        i;
    ngx_list_part_t  *part;
    ngx_regex_elt_t  *elts;

    opt = 0;

#if (NGX_HAVE_PCRE_JIT)
    {
    ngx_regex_conf_t    *rcf;
    ngx_pool_cleanup_t  *cln;

    rcf = (ngx_regex_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_regex_module);

    if (rcf->pcre_jit) {
        opt = PCRE_STUDY_JIT_COMPILE;

        /*
         * The PCRE JIT compiler uses mmap for its executable codes, so we
         * have to explicitly call the pcre_free_study() function to free
         * this memory.
         */

        cln = ngx_pool_cleanup_add(cycle->pool, 0);
        if (cln == NULL) {
            return NGX_ERROR;
        }

        cln->handler = ngx_pcre_free_studies;
        cln->data = ngx_pcre_studies;
    }
    }
#endif

    ngx_regex_malloc_init(cycle->pool);

    part = &ngx_pcre_studies->part;
    elts = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            elts = part->elts;
            i = 0;
        }

        elts[i].regex->extra = pcre_study(elts[i].regex->code, opt, &errstr);

        if (errstr != NULL) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                          "pcre_study() failed: %s in \"%s\"",
                          errstr, elts[i].name);
        }

#if (NGX_HAVE_PCRE_JIT)
        if (opt & PCRE_STUDY_JIT_COMPILE) {
            int jit, n;

            jit = 0;
            n = pcre_fullinfo(elts[i].regex->code, elts[i].regex->extra,
                              PCRE_INFO_JIT, &jit);

            if (n != 0 || jit != 1) {
                ngx_log_error(NGX_LOG_INFO, cycle->log, 0,
                              "JIT compiler does not support pattern: \"%s\"",
                              elts[i].name);
            }
        }
#endif
    }

    ngx_regex_malloc_done();

    ngx_pcre_studies = NULL;

    return NGX_OK;
}