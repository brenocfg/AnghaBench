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
struct data {size_t i; size_t* data; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (size_t,size_t) ; 
 int /*<<< orphan*/  ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_TRUE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  POOL_add (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,struct data*) ; 
 int /*<<< orphan*/ * POOL_create (size_t,size_t) ; 
 int /*<<< orphan*/  POOL_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fn ; 

__attribute__((used)) static int testOrder(size_t numThreads, size_t queueSize)
{
  struct data data;
  POOL_ctx* const ctx = POOL_create(numThreads, queueSize);
  ASSERT_TRUE(ctx);
  data.i = 0;
  ASSERT_FALSE(ZSTD_pthread_mutex_init(&data.mutex, NULL));
  { size_t i;
    for (i = 0; i < 16; ++i) {
      POOL_add(ctx, &fn, &data);
    }
  }
  POOL_free(ctx);
  ASSERT_EQ(16, data.i);
  { size_t i;
    for (i = 0; i < data.i; ++i) {
      ASSERT_EQ(i, data.data[i]);
    }
  }
  ZSTD_pthread_mutex_destroy(&data.mutex);
  return 0;
}