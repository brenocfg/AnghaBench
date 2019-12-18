#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum nss_status { ____Placeholder_nss_status } nss_status ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ GetentData ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SIGNALS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NSS_SIGNALS_BLOCK ; 
 int NSS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systemd_endent (TYPE_1__*) ; 

__attribute__((used)) static enum nss_status nss_systemd_endent(GetentData *p) {
        PROTECT_ERRNO;
        BLOCK_SIGNALS(NSS_SIGNALS_BLOCK);

        assert_se(pthread_mutex_lock(&p->mutex) == 0);
        systemd_endent(p);
        assert_se(pthread_mutex_unlock(&p->mutex) == 0);

        return NSS_STATUS_SUCCESS;
}