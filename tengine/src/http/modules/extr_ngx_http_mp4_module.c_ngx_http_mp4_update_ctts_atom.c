#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  size; } ;
typedef  TYPE_3__ ngx_mp4_ctts_atom_t ;
struct TYPE_14__ {size_t composition_offset_entries; size_t size; TYPE_2__* out; } ;
typedef  TYPE_4__ ngx_http_mp4_trak_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {TYPE_1__ file; } ;
typedef  TYPE_5__ ngx_http_mp4_file_t ;
struct TYPE_16__ {int last; int pos; } ;
typedef  TYPE_6__ ngx_buf_t ;
struct TYPE_12__ {TYPE_6__* buf; } ;

/* Variables and functions */
 size_t NGX_HTTP_MP4_CTTS_ATOM ; 
 size_t NGX_HTTP_MP4_CTTS_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_mp4_crop_ctts_data (TYPE_5__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
ngx_http_mp4_update_ctts_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    size_t                atom_size;
    ngx_buf_t            *atom, *data;
    ngx_mp4_ctts_atom_t  *ctts_atom;

    /*
     * mdia.minf.stbl.ctts updating requires trak->start_sample
     * from mdia.minf.stbl.stts which depends on value from mdia.mdhd
     * atom which may reside after mdia.minf
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 ctts atom update");

    data = trak->out[NGX_HTTP_MP4_CTTS_DATA].buf;

    if (data == NULL) {
        return;
    }

    ngx_http_mp4_crop_ctts_data(mp4, trak, 1);
    ngx_http_mp4_crop_ctts_data(mp4, trak, 0);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "composition offset entries:%uD",
                   trak->composition_offset_entries);

    if (trak->composition_offset_entries == 0) {
        trak->out[NGX_HTTP_MP4_CTTS_ATOM].buf = NULL;
        trak->out[NGX_HTTP_MP4_CTTS_DATA].buf = NULL;
        return;
    }

    atom_size = sizeof(ngx_mp4_ctts_atom_t) + (data->last - data->pos);
    trak->size += atom_size;

    atom = trak->out[NGX_HTTP_MP4_CTTS_ATOM].buf;
    ctts_atom = (ngx_mp4_ctts_atom_t *) atom->pos;

    ngx_mp4_set_32value(ctts_atom->size, atom_size);
    ngx_mp4_set_32value(ctts_atom->entries, trak->composition_offset_entries);

    return;
}