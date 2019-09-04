#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int content_length_n; } ;
struct TYPE_10__ {TYPE_1__ headers_out; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_11__ {int wbits; int memlevel; int allocated; int intel; } ;
typedef  TYPE_3__ ngx_http_gzip_ctx_t ;
struct TYPE_12__ {int wbits; int memlevel; int level; } ;
typedef  TYPE_4__ ngx_http_gzip_conf_t ;

/* Variables and functions */
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_gzip_assume_intel ; 
 int /*<<< orphan*/  ngx_http_gzip_filter_module ; 
 int ngx_max (int,int) ; 

__attribute__((used)) static void
ngx_http_gzip_filter_memory(ngx_http_request_t *r, ngx_http_gzip_ctx_t *ctx)
{
    int                    wbits, memlevel;
    ngx_http_gzip_conf_t  *conf;

    conf = ngx_http_get_module_loc_conf(r, ngx_http_gzip_filter_module);

    wbits = conf->wbits;
    memlevel = conf->memlevel;

    if (r->headers_out.content_length_n > 0) {

        /* the actual zlib window size is smaller by 262 bytes */

        while (r->headers_out.content_length_n < ((1 << (wbits - 1)) - 262)) {
            wbits--;
            memlevel--;
        }

        if (memlevel < 1) {
            memlevel = 1;
        }
    }

    ctx->wbits = wbits;
    ctx->memlevel = memlevel;

    /*
     * We preallocate a memory for zlib in one buffer (200K-400K), this
     * decreases a number of malloc() and free() calls and also probably
     * decreases a number of syscalls (sbrk()/mmap() and so on).
     * Besides we free the memory as soon as a gzipping will complete
     * and do not wait while a whole response will be sent to a client.
     *
     * 8K is for zlib deflate_state, it takes
     *  *) 5816 bytes on i386 and sparc64 (32-bit mode)
     *  *) 5920 bytes on amd64 and sparc64
     */

    if (!ngx_http_gzip_assume_intel) {
        ctx->allocated = 8192 + (1 << (wbits + 2)) + (1 << (memlevel + 9));

    } else {
        /*
         * A zlib variant from Intel, https://github.com/jtkukunas/zlib.
         * It can force window bits to 13 for fast compression level,
         * on processors with SSE 4.2 it uses 64K hash instead of scaling
         * it from the specified memory level, and also introduces
         * 16-byte padding in one out of the two window-sized buffers.
         */

        if (conf->level == 1) {
            wbits = ngx_max(wbits, 13);
        }

        ctx->allocated = 8192 + 16 + (1 << (wbits + 2))
                         + (1 << (ngx_max(memlevel, 8) + 8))
                         + (1 << (memlevel + 8));
        ctx->intel = 1;
    }
}