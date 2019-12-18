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
struct TYPE_4__ {int /*<<< orphan*/  mut; } ;
typedef  TYPE_1__ abruptEndCanary_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_FALSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int testAbruptEnding_internal (TYPE_1__) ; 

__attribute__((used)) static int testAbruptEnding(void) {
    int result;
    abruptEndCanary_t test;

    memset(&test, 0, sizeof(test));
    ASSERT_FALSE( ZSTD_pthread_mutex_init(&test.mut, NULL) );

    result = testAbruptEnding_internal(test);

    ZSTD_pthread_mutex_destroy(&test.mut);
    return result;
}