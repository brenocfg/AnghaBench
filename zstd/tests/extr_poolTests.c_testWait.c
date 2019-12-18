#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct data {int dummy; } ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_TRUE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  POOL_add (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,struct data*) ; 
 int /*<<< orphan*/ * POOL_create (size_t,size_t) ; 
 int /*<<< orphan*/  POOL_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  waitFn ; 

__attribute__((used)) static int testWait(size_t numThreads, size_t queueSize) {
  struct data data;
  POOL_ctx* const ctx = POOL_create(numThreads, queueSize);
  ASSERT_TRUE(ctx);
  { size_t i;
    for (i = 0; i < 16; ++i) {
        POOL_add(ctx, &waitFn, &data);
    }
  }
  POOL_free(ctx);
  return 0;
}