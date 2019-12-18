#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
struct TYPE_5__ {int /*<<< orphan*/  workspace; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_1__ ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_cwksp_free (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 int ZSTD_cwksp_owns_buffer (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/  const) ; 

size_t ZSTD_freeCDict(ZSTD_CDict* cdict)
{
    if (cdict==NULL) return 0;   /* support free on NULL */
    {   ZSTD_customMem const cMem = cdict->customMem;
        int cdictInWorkspace = ZSTD_cwksp_owns_buffer(&cdict->workspace, cdict);
        ZSTD_cwksp_free(&cdict->workspace, cMem);
        if (!cdictInWorkspace) {
            ZSTD_free(cdict, cMem);
        }
        return 0;
    }
}