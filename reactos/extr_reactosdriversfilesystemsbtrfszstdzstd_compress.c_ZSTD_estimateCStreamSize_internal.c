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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;

/* Variables and functions */
 size_t ZSTD_estimateCStreamSize_usingCParams (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ZSTD_getCParams (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_estimateCStreamSize_internal(int compressionLevel)
{
    ZSTD_compressionParameters const cParams = ZSTD_getCParams(compressionLevel, 0, 0);
    return ZSTD_estimateCStreamSize_usingCParams(cParams);
}