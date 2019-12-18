#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * cstream; int /*<<< orphan*/  framelog; } ;
typedef  TYPE_1__ ZSTD_seekable_CStream ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCStream () ; 
 int /*<<< orphan*/  ZSTD_freeCStream (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_seekable_frameLog_allocVec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

ZSTD_seekable_CStream* ZSTD_seekable_createCStream()
{
    ZSTD_seekable_CStream* zcs = malloc(sizeof(ZSTD_seekable_CStream));

    if (zcs == NULL) return NULL;

    memset(zcs, 0, sizeof(*zcs));

    zcs->cstream = ZSTD_createCStream();
    if (zcs->cstream == NULL) goto failed1;

    if (ZSTD_isError(ZSTD_seekable_frameLog_allocVec(&zcs->framelog))) goto failed2;

    return zcs;

failed2:
    ZSTD_freeCStream(zcs->cstream);
failed1:
    free(zcs);
    return NULL;
}