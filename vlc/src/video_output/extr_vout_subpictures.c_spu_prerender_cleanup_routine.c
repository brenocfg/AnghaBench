#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spu_prerender_ctx_s {int /*<<< orphan*/  cleanuplock; int /*<<< orphan*/ ** pp_processed; int /*<<< orphan*/  fmtsrc; int /*<<< orphan*/  fmtdst; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_format_Clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu_prerender_cleanup_routine(void *priv)
{
    struct spu_prerender_ctx_s *ctx = priv;
    video_format_Clean(&ctx->fmtdst);
    video_format_Clean(&ctx->fmtsrc);
    *ctx->pp_processed = NULL;
    vlc_mutex_unlock(ctx->cleanuplock);
}