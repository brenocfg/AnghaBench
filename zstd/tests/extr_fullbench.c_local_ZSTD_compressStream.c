#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_9__ {int /*<<< orphan*/  cParams; TYPE_4__ fParams; } ;
typedef  TYPE_1__ ZSTD_parameters ;
struct TYPE_10__ {size_t size; size_t pos; void* dst; } ;
typedef  TYPE_2__ ZSTD_outBuffer ;
struct TYPE_11__ {size_t size; scalar_t__ pos; void const* src; } ;
typedef  TYPE_3__ ZSTD_inBuffer ;
typedef  TYPE_4__ ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_compressStream (int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ZSTD_endStream (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_initCStream_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cstream ; 

__attribute__((used)) static size_t
local_ZSTD_compressStream(const void* src, size_t srcSize,
                          void* dst, size_t dstCapacity,
                          void* payload)
{
    ZSTD_outBuffer buffOut;
    ZSTD_inBuffer buffIn;
    ZSTD_parameters p;
    ZSTD_frameParameters f = {1 /* contentSizeHeader*/, 0, 0};
    p.fParams = f;
    p.cParams = *(ZSTD_compressionParameters*)payload;
    ZSTD_initCStream_advanced(g_cstream, NULL, 0, p, ZSTD_CONTENTSIZE_UNKNOWN);
    buffOut.dst = dst;
    buffOut.size = dstCapacity;
    buffOut.pos = 0;
    buffIn.src = src;
    buffIn.size = srcSize;
    buffIn.pos = 0;
    ZSTD_compressStream(g_cstream, &buffOut, &buffIn);
    ZSTD_endStream(g_cstream, &buffOut);
    return buffOut.pos;
}