#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  out_buf ;
struct TYPE_6__ {scalar_t__ avail_in; int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  next_in; } ;
struct TYPE_5__ {int in_finish; int flags; size_t sec_size; int write_error; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  buf_cond; TYPE_3__ zstrm; int /*<<< orphan*/  fp; int /*<<< orphan*/  rc4_key; scalar_t__ canceled; scalar_t__ in_full; scalar_t__ in_avail; TYPE_1__* p_buf; TYPE_1__* buffer; } ;
typedef  TYPE_2__ mm_backup_ctx ;
struct TYPE_4__ {scalar_t__ avail; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int MMBAK_FLAG_NO_CIPHER ; 
 int OUTPUT_BUFFER_SIZE ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Z_BUF_ERROR ; 
 int /*<<< orphan*/  Z_FINISH ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int deflate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 size_t fwrite (int /*<<< orphan*/  const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *write_thread_entry(void *ud)
{
    mm_backup_ctx *ctx = (mm_backup_ctx *) ud;

    for (;;) {
        int finish;

        pthread_mutex_lock(&ctx->buf_lock);
        {
            while (!ctx->in_avail && !ctx->in_finish && !ctx->canceled)
                pthread_cond_wait(&ctx->buf_cond, &ctx->buf_lock);

            ctx->zstrm.next_in = ctx->p_buf->data;
            ctx->zstrm.avail_in = ctx->p_buf->avail;
            finish = ctx->in_finish;

            ctx->p_buf = (ctx->p_buf == &ctx->buffer[0]) ? &ctx->buffer[1]
                                                         : &ctx->buffer[0];
            ctx->p_buf->avail = 0;

            ctx->in_avail = 0;
            ctx->in_full = 0;
        }
        pthread_mutex_unlock(&ctx->buf_lock);
        pthread_cond_signal(&ctx->buf_cond);

        int ret;
        uint8_t out_buf[OUTPUT_BUFFER_SIZE];

        if (ctx->canceled)
            return NULL;
        do {
            ctx->zstrm.next_out = out_buf;
            ctx->zstrm.avail_out = sizeof(out_buf);
            ret = deflate(&ctx->zstrm, finish ? Z_FINISH : Z_NO_FLUSH);
            if (ret == Z_BUF_ERROR)
                break;
            if (ret != Z_OK && ret != Z_STREAM_END)
                goto bail;

            uint_t out_len = sizeof(out_buf) - ctx->zstrm.avail_out;
            if ((ctx->flags & MMBAK_FLAG_NO_CIPHER) == 0)
                RC4(&ctx->rc4_key, out_len, out_buf, out_buf);

            const uint8_t *p = out_buf;
            while (out_len > 0) {
                size_t ret = fwrite(p, 1, out_len, ctx->fp);
                if (ret == 0 && ferror(ctx->fp))
                    goto bail;
                out_len -= ret;
                p += ret;
                ctx->sec_size += ret;
            }
        } while (ctx->zstrm.avail_out == 0 && ret != Z_STREAM_END);
        if (ctx->zstrm.avail_in != 0)
            goto bail;

        if (ret == Z_STREAM_END)
            break;
    }
    return NULL;

bail:
    pthread_mutex_lock(&ctx->buf_lock);
    ctx->write_error = 1;
    pthread_cond_signal(&ctx->buf_cond);
    pthread_mutex_unlock(&ctx->buf_lock);
    return NULL;
}