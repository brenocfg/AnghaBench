#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_22__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int off_t ;
typedef  int ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_24__ {scalar_t__ num; int /*<<< orphan*/  size; } ;
struct TYPE_29__ {int upstream_eof; int upstream_error; int upstream_done; scalar_t__ preread_size; int read; int limit_rate; int start_sec; int read_length; scalar_t__ allocated; scalar_t__ output_ctx; int upstream_blocked; scalar_t__ max_temp_file_size; scalar_t__ (* input_filter ) (TYPE_5__*,TYPE_7__*) ;int length; int /*<<< orphan*/  log; int /*<<< orphan*/ * buf_to_file; scalar_t__ in; scalar_t__ cacheable; int /*<<< orphan*/  pool; TYPE_6__* free_raw_bufs; scalar_t__ free_bufs; int /*<<< orphan*/  num; TYPE_14__* upstream; scalar_t__ single_buf; TYPE_4__* temp_file; TYPE_3__* downstream; TYPE_1__ bufs; TYPE_6__* preread_bufs; } ;
typedef  TYPE_5__ ngx_event_pipe_t ;
struct TYPE_30__ {TYPE_7__* buf; struct TYPE_30__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_31__ {scalar_t__ end; scalar_t__ last; int pos; int /*<<< orphan*/  start; int /*<<< orphan*/ * shadow; scalar_t__ num; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_28__ {scalar_t__ offset; } ;
struct TYPE_27__ {scalar_t__ data; TYPE_2__* write; } ;
struct TYPE_26__ {int /*<<< orphan*/  delayed; scalar_t__ ready; } ;
struct TYPE_25__ {scalar_t__ ready; int delayed; } ;
struct TYPE_23__ {scalar_t__ (* recv_chain ) (TYPE_14__*,TYPE_6__*,int) ;TYPE_22__* read; } ;

/* Variables and functions */
 scalar_t__ NGX_ABORT ; 
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_22__*,int) ; 
 TYPE_6__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_event_pipe_remove_shadow_links (TYPE_7__*) ; 
 scalar_t__ ngx_event_pipe_write_chain_to_temp_file (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ngx_time () ; 
 scalar_t__ stub1 (TYPE_14__*,TYPE_6__*,int) ; 
 scalar_t__ stub2 (TYPE_5__*,TYPE_7__*) ; 
 scalar_t__ stub3 (TYPE_5__*,TYPE_7__*) ; 
 scalar_t__ stub4 (TYPE_5__*,TYPE_7__*) ; 

__attribute__((used)) static ngx_int_t
ngx_event_pipe_read_upstream(ngx_event_pipe_t *p)
{
    off_t         limit;
    ssize_t       n, size;
    ngx_int_t     rc;
    ngx_buf_t    *b;
    ngx_msec_t    delay;
    ngx_chain_t  *chain, *cl, *ln;

    if (p->upstream_eof || p->upstream_error || p->upstream_done) {
        return NGX_OK;
    }

#if (NGX_THREADS)

    if (p->aio) {
        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe read upstream: aio");
        return NGX_AGAIN;
    }

    if (p->writing) {
        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe read upstream: writing");

        rc = ngx_event_pipe_write_chain_to_temp_file(p);

        if (rc != NGX_OK) {
            return rc;
        }
    }

#endif

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                   "pipe read upstream: %d", p->upstream->read->ready);

    for ( ;; ) {

        if (p->upstream_eof || p->upstream_error || p->upstream_done) {
            break;
        }

        if (p->preread_bufs == NULL && !p->upstream->read->ready) {
            break;
        }

        if (p->preread_bufs) {

            /* use the pre-read bufs if they exist */

            chain = p->preread_bufs;
            p->preread_bufs = NULL;
            n = p->preread_size;

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                           "pipe preread: %z", n);

            if (n) {
                p->read = 1;
            }

        } else {

#if (NGX_HAVE_KQUEUE)

            /*
             * kqueue notifies about the end of file or a pending error.
             * This test allows not to allocate a buf on these conditions
             * and not to call c->recv_chain().
             */

            if (p->upstream->read->available == 0
                && p->upstream->read->pending_eof)
            {
                p->upstream->read->ready = 0;
                p->upstream->read->eof = 1;
                p->upstream_eof = 1;
                p->read = 1;

                if (p->upstream->read->kq_errno) {
                    p->upstream->read->error = 1;
                    p->upstream_error = 1;
                    p->upstream_eof = 0;

                    ngx_log_error(NGX_LOG_ERR, p->log,
                                  p->upstream->read->kq_errno,
                                  "kevent() reported that upstream "
                                  "closed connection");
                }

                break;
            }
#endif

            if (p->limit_rate) {
                if (p->upstream->read->delayed) {
                    break;
                }

                limit = (off_t) p->limit_rate * (ngx_time() - p->start_sec + 1)
                        - p->read_length;

                if (limit <= 0) {
                    p->upstream->read->delayed = 1;
                    delay = (ngx_msec_t) (- limit * 1000 / p->limit_rate + 1);
                    ngx_add_timer(p->upstream->read, delay);
                    break;
                }

            } else {
                limit = 0;
            }

            if (p->free_raw_bufs) {

                /* use the free bufs if they exist */

                chain = p->free_raw_bufs;
                if (p->single_buf) {
                    p->free_raw_bufs = p->free_raw_bufs->next;
                    chain->next = NULL;
                } else {
                    p->free_raw_bufs = NULL;
                }

            } else if (p->allocated < p->bufs.num) {

                /* allocate a new buf if it's still allowed */

                b = ngx_create_temp_buf(p->pool, p->bufs.size);
                if (b == NULL) {
                    return NGX_ABORT;
                }

                p->allocated++;

                chain = ngx_alloc_chain_link(p->pool);
                if (chain == NULL) {
                    return NGX_ABORT;
                }

                chain->buf = b;
                chain->next = NULL;

            } else if (!p->cacheable
                       && p->downstream->data == p->output_ctx
                       && p->downstream->write->ready
                       && !p->downstream->write->delayed)
            {
                /*
                 * if the bufs are not needed to be saved in a cache and
                 * a downstream is ready then write the bufs to a downstream
                 */

                p->upstream_blocked = 1;

                ngx_log_debug0(NGX_LOG_DEBUG_EVENT, p->log, 0,
                               "pipe downstream ready");

                break;

            } else if (p->cacheable
                       || p->temp_file->offset < p->max_temp_file_size)
            {

                /*
                 * if it is allowed, then save some bufs from p->in
                 * to a temporary file, and add them to a p->out chain
                 */

                rc = ngx_event_pipe_write_chain_to_temp_file(p);

                ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                               "pipe temp offset: %O", p->temp_file->offset);

                if (rc == NGX_BUSY) {
                    break;
                }

                if (rc != NGX_OK) {
                    return rc;
                }

                chain = p->free_raw_bufs;
                if (p->single_buf) {
                    p->free_raw_bufs = p->free_raw_bufs->next;
                    chain->next = NULL;
                } else {
                    p->free_raw_bufs = NULL;
                }

            } else {

                /* there are no bufs to read in */

                ngx_log_debug0(NGX_LOG_DEBUG_EVENT, p->log, 0,
                               "no pipe bufs to read in");

                break;
            }

            n = p->upstream->recv_chain(p->upstream, chain, limit);

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                           "pipe recv chain: %z", n);

            if (p->free_raw_bufs) {
                chain->next = p->free_raw_bufs;
            }
            p->free_raw_bufs = chain;

            if (n == NGX_ERROR) {
                p->upstream_error = 1;
                break;
            }

            if (n == NGX_AGAIN) {
                if (p->single_buf) {
                    ngx_event_pipe_remove_shadow_links(chain->buf);
                }

                break;
            }

            p->read = 1;

            if (n == 0) {
                p->upstream_eof = 1;
                break;
            }
        }

        delay = p->limit_rate ? (ngx_msec_t) n * 1000 / p->limit_rate : 0;

        p->read_length += n;
        cl = chain;
        p->free_raw_bufs = NULL;

        while (cl && n > 0) {

            ngx_event_pipe_remove_shadow_links(cl->buf);

            size = cl->buf->end - cl->buf->last;

            if (n >= size) {
                cl->buf->last = cl->buf->end;

                /* STUB */ cl->buf->num = p->num++;

                if (p->input_filter(p, cl->buf) == NGX_ERROR) {
                    return NGX_ABORT;
                }

                n -= size;
                ln = cl;
                cl = cl->next;
                ngx_free_chain(p->pool, ln);

            } else {
                cl->buf->last += n;
                n = 0;
            }
        }

        if (cl) {
            for (ln = cl; ln->next; ln = ln->next) { /* void */ }

            ln->next = p->free_raw_bufs;
            p->free_raw_bufs = cl;
        }

        if (delay > 0) {
            p->upstream->read->delayed = 1;
            ngx_add_timer(p->upstream->read, delay);
            break;
        }
    }

#if (NGX_DEBUG)

    for (cl = p->busy; cl; cl = cl->next) {
        ngx_log_debug8(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe buf busy s:%d t:%d f:%d "
                       "%p, pos %p, size: %z "
                       "file: %O, size: %O",
                       (cl->buf->shadow ? 1 : 0),
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

    for (cl = p->out; cl; cl = cl->next) {
        ngx_log_debug8(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe buf out  s:%d t:%d f:%d "
                       "%p, pos %p, size: %z "
                       "file: %O, size: %O",
                       (cl->buf->shadow ? 1 : 0),
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

    for (cl = p->in; cl; cl = cl->next) {
        ngx_log_debug8(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe buf in   s:%d t:%d f:%d "
                       "%p, pos %p, size: %z "
                       "file: %O, size: %O",
                       (cl->buf->shadow ? 1 : 0),
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

    for (cl = p->free_raw_bufs; cl; cl = cl->next) {
        ngx_log_debug8(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe buf free s:%d t:%d f:%d "
                       "%p, pos %p, size: %z "
                       "file: %O, size: %O",
                       (cl->buf->shadow ? 1 : 0),
                       cl->buf->temporary, cl->buf->in_file,
                       cl->buf->start, cl->buf->pos,
                       cl->buf->last - cl->buf->pos,
                       cl->buf->file_pos,
                       cl->buf->file_last - cl->buf->file_pos);
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, p->log, 0,
                   "pipe length: %O", p->length);

#endif

    if (p->free_raw_bufs && p->length != -1) {
        cl = p->free_raw_bufs;

        if (cl->buf->last - cl->buf->pos >= p->length) {

            p->free_raw_bufs = cl->next;

            /* STUB */ cl->buf->num = p->num++;

            if (p->input_filter(p, cl->buf) == NGX_ERROR) {
                return NGX_ABORT;
            }

            ngx_free_chain(p->pool, cl);
        }
    }

    if (p->length == 0) {
        p->upstream_done = 1;
        p->read = 1;
    }

    if ((p->upstream_eof || p->upstream_error) && p->free_raw_bufs) {

        /* STUB */ p->free_raw_bufs->buf->num = p->num++;

        if (p->input_filter(p, p->free_raw_bufs->buf) == NGX_ERROR) {
            return NGX_ABORT;
        }

        p->free_raw_bufs = p->free_raw_bufs->next;

        if (p->free_bufs && p->buf_to_file == NULL) {
            for (cl = p->free_raw_bufs; cl; cl = cl->next) {
                if (cl->buf->shadow == NULL) {
                    ngx_pfree(p->pool, cl->buf->start);
                }
            }
        }
    }

    if (p->cacheable && (p->in || p->buf_to_file)) {

        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, p->log, 0,
                       "pipe write chain");

        rc = ngx_event_pipe_write_chain_to_temp_file(p);

        if (rc != NGX_OK) {
            return rc;
        }
    }

    return NGX_OK;
}