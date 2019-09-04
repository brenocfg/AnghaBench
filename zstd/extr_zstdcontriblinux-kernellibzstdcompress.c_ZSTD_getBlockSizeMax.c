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
struct TYPE_5__ {int windowLog; } ;
struct TYPE_6__ {TYPE_1__ cParams; } ;
struct TYPE_7__ {TYPE_2__ params; } ;
typedef  TYPE_3__ ZSTD_CCtx ;

/* Variables and functions */
 size_t MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 

size_t ZSTD_getBlockSizeMax(ZSTD_CCtx *cctx) { return MIN(ZSTD_BLOCKSIZE_ABSOLUTEMAX, 1 << cctx->params.cParams.windowLog); }