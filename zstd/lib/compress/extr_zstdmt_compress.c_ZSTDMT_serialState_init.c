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
struct TYPE_4__ {int /*<<< orphan*/  ldmWindowCond; int /*<<< orphan*/  ldmWindowMutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ serialState_t ;

/* Variables and functions */
 int ZSTD_pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ZSTDMT_serialState_init(serialState_t* serialState)
{
    int initError = 0;
    memset(serialState, 0, sizeof(*serialState));
    initError |= ZSTD_pthread_mutex_init(&serialState->mutex, NULL);
    initError |= ZSTD_pthread_cond_init(&serialState->cond, NULL);
    initError |= ZSTD_pthread_mutex_init(&serialState->ldmWindowMutex, NULL);
    initError |= ZSTD_pthread_cond_init(&serialState->ldmWindowCond, NULL);
    return initError;
}