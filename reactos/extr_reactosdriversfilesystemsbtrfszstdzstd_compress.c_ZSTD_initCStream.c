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
typedef  int /*<<< orphan*/  ZSTD_CStream ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_initCStream_srcSize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

size_t ZSTD_initCStream(ZSTD_CStream* zcs, int compressionLevel)
{
    DEBUGLOG(4, "ZSTD_initCStream");
    return ZSTD_initCStream_srcSize(zcs, compressionLevel, ZSTD_CONTENTSIZE_UNKNOWN);
}