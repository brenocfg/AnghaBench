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
struct TYPE_3__ {int in_finish; int /*<<< orphan*/  buf_cond; int /*<<< orphan*/  buf_lock; scalar_t__ write_error; } ;
typedef  TYPE_1__ mm_backup_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE_ (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dump_write_end(mm_backup_ctx *ctx)
{
    int ret;

    // flush padding input.
    pthread_mutex_lock(&ctx->buf_lock);
    {
        ctx->in_finish = 1;
        if (ctx->write_error) {
            LOGE_("Writing thread reported error.");
            ret = -1;
        } else
            ret = 0;
    }
    pthread_mutex_unlock(&ctx->buf_lock);
    pthread_cond_signal(&ctx->buf_cond);

    return ret;
}