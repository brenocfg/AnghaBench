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
struct TYPE_4__ {int /*<<< orphan*/  maxWindowSize; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_MAXWINDOWSIZE_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_f_zstd1 ; 
 int /*<<< orphan*/  ZSTD_initDStream (TYPE_1__*) ; 

void ZSTD_DCtx_reset(ZSTD_DCtx* dctx)
{
    (void)ZSTD_initDStream(dctx);
    dctx->format = ZSTD_f_zstd1;
    dctx->maxWindowSize = ZSTD_MAXWINDOWSIZE_DEFAULT;
}