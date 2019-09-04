#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ off_t ;
struct TYPE_10__ {TYPE_2__* out; } ;
typedef  TYPE_3__ ngx_http_mp4_trak_t ;
struct TYPE_8__ {int /*<<< orphan*/  log; } ;
struct TYPE_11__ {TYPE_1__ file; } ;
typedef  TYPE_4__ ngx_http_mp4_file_t ;
struct TYPE_12__ {scalar_t__ last; scalar_t__ pos; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_9__ {TYPE_5__* buf; } ;

/* Variables and functions */
 size_t NGX_HTTP_MP4_CO64_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mp4_get_64value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_mp4_set_64value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_mp4_adjust_co64_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak, off_t adjustment)
{
    uint64_t    offset, *entry, *end;
    ngx_buf_t  *data;

    /*
     * moov.trak.mdia.minf.stbl.co64 adjustment requires
     * minimal start offset of all traks and new moov atom size
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 co64 atom adjustment");

    data = trak->out[NGX_HTTP_MP4_CO64_DATA].buf;
    entry = (uint64_t *) data->pos;
    end = (uint64_t *) data->last;

    while (entry < end) {
        offset = ngx_mp4_get_64value(entry);
        offset += adjustment;
        ngx_mp4_set_64value(entry, offset);
        entry++;
    }
}