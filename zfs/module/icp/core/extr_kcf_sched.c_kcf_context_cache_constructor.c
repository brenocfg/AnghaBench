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
struct TYPE_2__ {int /*<<< orphan*/  kc_in_use_lock; scalar_t__ kc_refcnt; } ;
typedef  TYPE_1__ kcf_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kcf_context_cache_constructor(void *buf, void *cdrarg, int kmflags)
{
	kcf_context_t *kctx = (kcf_context_t *)buf;

	kctx->kc_refcnt = 0;
	mutex_init(&kctx->kc_in_use_lock, NULL, MUTEX_DEFAULT, NULL);

	return (0);
}