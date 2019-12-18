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
struct TYPE_5__ {TYPE_2__* entries; } ;
struct TYPE_6__ {TYPE_1__ seekTable; int /*<<< orphan*/  dstream; } ;
typedef  TYPE_2__ ZSTD_seekable ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

size_t ZSTD_seekable_free(ZSTD_seekable* zs)
{
    if (zs == NULL) return 0; /* support free on null */
    ZSTD_freeDStream(zs->dstream);
    free(zs->seekTable.entries);
    free(zs);

    return 0;
}