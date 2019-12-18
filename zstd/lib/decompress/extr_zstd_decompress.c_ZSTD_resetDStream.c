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
struct TYPE_4__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_DCtx_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 
 size_t ZSTD_startingInputLength (int /*<<< orphan*/ ) ; 

size_t ZSTD_resetDStream(ZSTD_DStream* dctx)
{
    FORWARD_IF_ERROR(ZSTD_DCtx_reset(dctx, ZSTD_reset_session_only));
    return ZSTD_startingInputLength(dctx->format);
}