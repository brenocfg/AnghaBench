#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_shmtx_sh_t ;
struct TYPE_10__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {size_t size; int /*<<< orphan*/ * addr; int /*<<< orphan*/  log; TYPE_1__ name; } ;
typedef  TYPE_2__ ngx_shm_t ;
struct TYPE_14__ {scalar_t__ spin; } ;
struct TYPE_12__ {TYPE_5__ ngx_http_tfs_kp_mutex; int /*<<< orphan*/ * ngx_http_tfs_kp_mutex_ptr; } ;
typedef  TYPE_3__ ngx_http_tfs_timers_lock_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_cycle_t ;
typedef  int /*<<< orphan*/  ngx_atomic_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_shm_alloc (TYPE_2__*) ; 
 scalar_t__ ngx_shmtx_create (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ngx_http_tfs_timers_lock_t *
ngx_http_tfs_timers_init(ngx_cycle_t *cycle,
    u_char *lock_file)
{
    u_char                     *shared;
    size_t                      size;
    ngx_shm_t                   shm;
    ngx_http_tfs_timers_lock_t *lock;

    /* cl should be equal or bigger than cache line size */

    size = 128; /* ngx_http_tfs_kp_mutex */

    shm.size = size;
    shm.name.len = sizeof("nginx_tfs_keepalive_zone");
    shm.name.data = (u_char *) "nginx_tfs_keepalive_zone";
    shm.log = cycle->log;

    if (ngx_shm_alloc(&shm) != NGX_OK) {
        return NULL;
    }

    shared = shm.addr;

    lock = ngx_palloc(cycle->pool, sizeof(ngx_http_tfs_timers_lock_t));
    if (lock == NULL) {
        return NULL;
    }

    lock->ngx_http_tfs_kp_mutex_ptr = (ngx_atomic_t *) shared;
    lock->ngx_http_tfs_kp_mutex.spin = (ngx_uint_t) -1;

#if defined(nginx_version) && (nginx_version > 1001008)

    if (ngx_shmtx_create(&lock->ngx_http_tfs_kp_mutex,
                         (ngx_shmtx_sh_t *) shared, lock_file)
        != NGX_OK)
    {
        return NULL;
    }

#else

    if (ngx_shmtx_create(&lock->ngx_http_tfs_kp_mutex, shared, lock_file)
        != NGX_OK)
    {
        return NULL;
    }
#endif

    return lock;
}