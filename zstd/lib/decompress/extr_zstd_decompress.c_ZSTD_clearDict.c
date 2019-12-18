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
struct TYPE_3__ {int /*<<< orphan*/  dictUses; int /*<<< orphan*/ * ddict; int /*<<< orphan*/ * ddictLocal; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_dont_use ; 
 int /*<<< orphan*/  ZSTD_freeDDict (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTD_clearDict(ZSTD_DCtx* dctx)
{
    ZSTD_freeDDict(dctx->ddictLocal);
    dctx->ddictLocal = NULL;
    dctx->ddict = NULL;
    dctx->dictUses = ZSTD_dont_use;
}