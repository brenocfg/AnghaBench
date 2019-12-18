#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int tableLen; TYPE_1__* entries; } ;
struct TYPE_7__ {TYPE_2__ seekTable; } ;
typedef  TYPE_3__ ZSTD_seekable ;
struct TYPE_5__ {size_t cOffset; } ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frameIndex_tooLarge ; 

size_t ZSTD_seekable_getFrameCompressedSize(ZSTD_seekable* const zs, unsigned frameIndex)
{
    if (frameIndex >= zs->seekTable.tableLen) return ERROR(frameIndex_tooLarge);
    return zs->seekTable.entries[frameIndex + 1].cOffset -
           zs->seekTable.entries[frameIndex].cOffset;
}