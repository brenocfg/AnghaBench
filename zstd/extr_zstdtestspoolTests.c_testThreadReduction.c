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
typedef  int /*<<< orphan*/  test ;
struct TYPE_4__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mut; } ;
typedef  TYPE_1__ poolTest_t ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_TRUE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * POOL_create (int,int) ; 
 int /*<<< orphan*/  POOL_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int testThreadReduction_internal (int /*<<< orphan*/ * const,TYPE_1__) ; 

__attribute__((used)) static int testThreadReduction(void) {
    int result;
    poolTest_t test;
    POOL_ctx* const ctx = POOL_create(4 /*nbThreads*/, 2 /*queueSize*/);

    ASSERT_TRUE(ctx);

    memset(&test, 0, sizeof(test));
    ASSERT_FALSE( ZSTD_pthread_mutex_init(&test.mut, NULL) );
    ASSERT_FALSE( ZSTD_pthread_cond_init(&test.cond, NULL) );

    result = testThreadReduction_internal(ctx, test);

    ZSTD_pthread_mutex_destroy(&test.mut);
    ZSTD_pthread_cond_destroy(&test.cond);
    POOL_free(ctx);

    return result;
}