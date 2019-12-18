#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {int /*<<< orphan*/  fails; int /*<<< orphan*/  reqs; int /*<<< orphan*/  used; int /*<<< orphan*/  total; } ;
typedef  TYPE_4__ ngx_slab_stat_t ;
struct TYPE_18__ {size_t slab; struct TYPE_18__* next; } ;
struct TYPE_17__ {int min_shift; size_t pfree; int /*<<< orphan*/  mutex; TYPE_4__* stats; int /*<<< orphan*/  end; int /*<<< orphan*/  start; TYPE_6__ free; } ;
typedef  TYPE_5__ ngx_slab_pool_t ;
typedef  TYPE_6__ ngx_slab_page_t ;
struct TYPE_14__ {scalar_t__ len; } ;
struct TYPE_15__ {int size; TYPE_2__ name; scalar_t__ addr; } ;
struct TYPE_19__ {TYPE_3__ shm; } ;
typedef  TYPE_7__ ngx_shm_zone_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_20__ {size_t nelts; TYPE_7__* elts; struct TYPE_20__* next; } ;
typedef  TYPE_8__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_21__ {int memory; int last_buf; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
typedef  TYPE_9__ ngx_buf_t ;
struct TYPE_13__ {TYPE_8__ part; } ;
struct TYPE_12__ {TYPE_1__ shared_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SLAB_PAGE_ENTRY_FORMAT ; 
 scalar_t__ NGX_SLAB_PAGE_ENTRY_SIZE ; 
 int /*<<< orphan*/  NGX_SLAB_SHM_FORMAT ; 
 scalar_t__ NGX_SLAB_SHM_SIZE ; 
 int /*<<< orphan*/  NGX_SLAB_SLOT_ENTRY_FORMAT ; 
 scalar_t__ NGX_SLAB_SLOT_ENTRY_SIZE ; 
 int /*<<< orphan*/  NGX_SLAB_SUMMARY_FORMAT ; 
 scalar_t__ NGX_SLAB_SUMMARY_SIZE ; 
 TYPE_11__* ngx_cycle ; 
 int ngx_pagesize_shift ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_slab_stat_buf(ngx_pool_t *pool, ngx_buf_t *b)
{
    u_char                       *p;
    size_t                        pz, size;
    ngx_uint_t                    i, k, n;
    ngx_shm_zone_t               *shm_zone;
    ngx_slab_pool_t              *shpool;
    ngx_slab_page_t              *page;
    ngx_slab_stat_t              *stats;
    volatile ngx_list_part_t     *part;

#define NGX_SLAB_SHM_SIZE               (sizeof("* shared memory: \n") - 1)
#define NGX_SLAB_SHM_FORMAT             "* shared memory: %V\n"
#define NGX_SLAB_SUMMARY_SIZE           \
    (3 * 12 + sizeof("total:(KB) free:(KB) size:(KB)\n") - 1)
#define NGX_SLAB_SUMMARY_FORMAT         \
    "total:%12z(KB) free:%12z(KB) size:%12z(KB)\n"
#define NGX_SLAB_PAGE_ENTRY_SIZE        \
    (12 + 2 * 16 + sizeof("pages:(KB) start: end:\n") - 1)
#define NGX_SLAB_PAGE_ENTRY_FORMAT      \
    "pages:%12z(KB) start:%p end:%p\n"
#define NGX_SLAB_SLOT_ENTRY_SIZE        \
    (12 * 5 + sizeof("slot:(Bytes) total: used: reqs: fails:\n") - 1)
#define NGX_SLAB_SLOT_ENTRY_FORMAT      \
    "slot:%12z(Bytes) total:%12z used:%12z reqs:%12z fails:%12z\n"

    pz = 0;

    /* query shared memory */

    part = &ngx_cycle->shared_memory.part;
    shm_zone = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            shm_zone = part->elts;
            i = 0;
        }

        pz += NGX_SLAB_SHM_SIZE + (size_t)shm_zone[i].shm.name.len;
        pz += NGX_SLAB_SUMMARY_SIZE;

        shpool = (ngx_slab_pool_t *) shm_zone[i].shm.addr;

        ngx_shmtx_lock(&shpool->mutex);

        for (page = shpool->free.next; page != &shpool->free; page = page->next) {
            pz += NGX_SLAB_PAGE_ENTRY_SIZE;
        }

        n = ngx_pagesize_shift - shpool->min_shift;

        ngx_shmtx_unlock(&shpool->mutex);

        for (k = 0; k < n; k++) {
            pz += NGX_SLAB_SLOT_ENTRY_SIZE;
        }

    }

    /* preallocate pz * 2 to make sure memory enough */
    p = ngx_palloc(pool, pz * 2);
    if (p == NULL) {
        return NGX_ERROR;
    }

    b->pos = p;

    size = 1 << ngx_pagesize_shift;

    part = &ngx_cycle->shared_memory.part;
    shm_zone = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }
            part = part->next;
            shm_zone = part->elts;
            i = 0;
        }

        shpool = (ngx_slab_pool_t *) shm_zone[i].shm.addr;

        p = ngx_snprintf(p, NGX_SLAB_SHM_SIZE + shm_zone[i].shm.name.len,
            NGX_SLAB_SHM_FORMAT, &shm_zone[i].shm.name);

        ngx_shmtx_lock(&shpool->mutex);

        p = ngx_snprintf(p, NGX_SLAB_SUMMARY_SIZE, NGX_SLAB_SUMMARY_FORMAT,
            shm_zone[i].shm.size / 1024, shpool->pfree * size / 1024,
            size / 1024, shpool->pfree);

        for (page = shpool->free.next; page != &shpool->free; page = page->next) {
            p = ngx_snprintf(p, NGX_SLAB_PAGE_ENTRY_SIZE,
                NGX_SLAB_PAGE_ENTRY_FORMAT, page->slab * size / 1024,
                shpool->start, shpool->end);
        }

        stats = shpool->stats;

        n = ngx_pagesize_shift - shpool->min_shift;

        for (k = 0; k < n; k++) {
            p = ngx_snprintf(p, NGX_SLAB_SLOT_ENTRY_SIZE, NGX_SLAB_SLOT_ENTRY_FORMAT,
                1 << (k + shpool->min_shift),
                stats[k].total, stats[k].used, stats[k].reqs, stats[k].fails);
        }

        ngx_shmtx_unlock(&shpool->mutex);
    }

    b->last = p;
    b->memory = 1;
    b->last_buf = 1;

    return NGX_OK;
}