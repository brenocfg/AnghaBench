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
struct TYPE_3__ {scalar_t__ hostageByte; scalar_t__ legacyVersion; scalar_t__ outEnd; scalar_t__ outStart; scalar_t__ inPos; scalar_t__ lhSize; int /*<<< orphan*/  stage; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 size_t ZSTD_frameHeaderSize_prefix ; 
 int /*<<< orphan*/  zdss_loadHeader ; 

size_t ZSTD_resetDStream(ZSTD_DStream *zds)
{
	zds->stage = zdss_loadHeader;
	zds->lhSize = zds->inPos = zds->outStart = zds->outEnd = 0;
	zds->legacyVersion = 0;
	zds->hostageByte = 0;
	return ZSTD_frameHeaderSize_prefix;
}