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
struct TYPE_4__ {scalar_t__ val; } ;
typedef  TYPE_1__ abruptEndCanary_t ;
typedef  int /*<<< orphan*/  POOL_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (scalar_t__,int const) ; 
 int /*<<< orphan*/  ASSERT_TRUE (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  POOL_add (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * POOL_create (int,int const) ; 
 int /*<<< orphan*/  POOL_free (int /*<<< orphan*/ * const) ; 
 scalar_t__ POOL_resize (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  waitIncFn ; 

__attribute__((used)) static int testAbruptEnding_internal(abruptEndCanary_t test)
{
    int const nbWaits = 16;

    POOL_ctx* const ctx = POOL_create(3 /*numThreads*/, nbWaits /*queueSize*/);
    ASSERT_TRUE(ctx);
    test.val = 0;

    {   int i;
        for (i=0; i<nbWaits; i++)
            POOL_add(ctx, &waitIncFn, &test);  /* all jobs pushed into queue */
    }
    ASSERT_EQ( POOL_resize(ctx, 1 /*numThreads*/) , 0 );   /* downsize numThreads, to try to break end condition */

    POOL_free(ctx);  /* must finish all jobs in queue before giving back control */
    ASSERT_EQ(test.val, nbWaits);
    return 0;
}