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
struct TYPE_4__ {int countdown; int /*<<< orphan*/  mut; scalar_t__ max; scalar_t__ val; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ poolTest_t ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (scalar_t__,int) ; 
 int /*<<< orphan*/  POOL_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ POOL_resize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitLongFn ; 

__attribute__((used)) static int testThreadReduction_internal(POOL_ctx* ctx, poolTest_t test)
{
    int const nbWaits = 16;

    test.countdown = nbWaits;
    test.val = 0;
    test.max = 0;

    {   int i;
        for (i=0; i<nbWaits; i++)
            POOL_add(ctx, &waitLongFn, &test);
    }
    ZSTD_pthread_mutex_lock(&test.mut);
    while (test.countdown > 0)
        ZSTD_pthread_cond_wait(&test.cond, &test.mut);
    ASSERT_EQ(test.val, 0);
    ASSERT_EQ(test.max, 4);
    ZSTD_pthread_mutex_unlock(&test.mut);

    ASSERT_EQ( POOL_resize(ctx, 2/*nbThreads*/) , 0 );
    test.countdown = nbWaits;
    test.val = 0;
    test.max = 0;
    {   int i;
        for (i=0; i<nbWaits; i++)
            POOL_add(ctx, &waitLongFn, &test);
    }
    ZSTD_pthread_mutex_lock(&test.mut);
    while (test.countdown > 0)
        ZSTD_pthread_cond_wait(&test.cond, &test.mut);
    ASSERT_EQ(test.val, 0);
    ASSERT_EQ(test.max, 2);
    ZSTD_pthread_mutex_unlock(&test.mut);

    return 0;
}