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
struct TYPE_4__ {int /*<<< orphan*/  framelog; int /*<<< orphan*/  cstream; } ;
typedef  TYPE_1__ ZSTD_seekable_CStream ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeCStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_seekable_frameLog_freeVec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

size_t ZSTD_seekable_freeCStream(ZSTD_seekable_CStream* zcs)
{
    if (zcs == NULL) return 0; /* support free on null */
    ZSTD_freeCStream(zcs->cstream);
    ZSTD_seekable_frameLog_freeVec(&zcs->framelog);
    free(zcs);

    return 0;
}