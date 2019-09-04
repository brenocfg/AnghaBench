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
typedef  int /*<<< orphan*/  redisReader ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_ERR_OOM ; 
 int /*<<< orphan*/  __redisReaderSetError (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void __redisReaderSetErrorOOM(redisReader *r) {
    __redisReaderSetError(r,REDIS_ERR_OOM,"Out of memory");
}