#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t bufferSize; int /*<<< orphan*/  poolMutex; } ;
typedef  TYPE_1__ ZSTDMT_bufferPool ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_setBufferSize(ZSTDMT_bufferPool* const bufPool, size_t const bSize)
{
    ZSTD_pthread_mutex_lock(&bufPool->poolMutex);
    DEBUGLOG(4, "ZSTDMT_setBufferSize: bSize = %u", (U32)bSize);
    bufPool->bufferSize = bSize;
    ZSTD_pthread_mutex_unlock(&bufPool->poolMutex);
}