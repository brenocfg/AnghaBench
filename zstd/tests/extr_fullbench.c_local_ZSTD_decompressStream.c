#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t size; size_t pos; void* dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {scalar_t__ pos; int /*<<< orphan*/  size; void* src; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_decompressStream (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_initDStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cSize ; 
 int /*<<< orphan*/  g_dstream ; 

__attribute__((used)) static size_t
local_ZSTD_decompressStream(const void* src, size_t srcSize,
                            void* dst, size_t dstCapacity,
                            void* buff2)
{
    ZSTD_outBuffer buffOut;
    ZSTD_inBuffer buffIn;
    (void)src; (void)srcSize;
    ZSTD_initDStream(g_dstream);
    buffOut.dst = dst;
    buffOut.size = dstCapacity;
    buffOut.pos = 0;
    buffIn.src = buff2;
    buffIn.size = g_cSize;
    buffIn.pos = 0;
    ZSTD_decompressStream(g_dstream, &buffOut, &buffIn);
    return buffOut.pos;
}