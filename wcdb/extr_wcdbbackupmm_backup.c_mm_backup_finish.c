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
struct TYPE_4__ {int canceled; int /*<<< orphan*/  zstrm; scalar_t__ fp; int /*<<< orphan*/  buf_cond; int /*<<< orphan*/  buf_lock; struct TYPE_4__* tabdesc; int /*<<< orphan*/  write_thread; } ;
typedef  TYPE_1__ mm_backup_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void mm_backup_finish(mm_backup_ctx *ctx)
{
    if (!ctx->canceled) {
        ctx->canceled = 1;
        pthread_cond_broadcast(&ctx->buf_cond);
        pthread_detach(ctx->write_thread);
    }

    free(ctx->tabdesc);
    pthread_mutex_destroy(&ctx->buf_lock);
    pthread_cond_destroy(&ctx->buf_cond);

    if (ctx->fp)
        fclose(ctx->fp);
    deflateEnd(&ctx->zstrm);
    free(ctx);
}