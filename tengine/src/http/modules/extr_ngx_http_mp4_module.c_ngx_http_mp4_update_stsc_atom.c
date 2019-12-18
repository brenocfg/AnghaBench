#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/  chunk; } ;
typedef  TYPE_4__ ngx_mp4_stsc_entry_t ;
struct TYPE_17__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ ngx_mp4_stsc_atom_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {int sample_to_chunk_entries; size_t size; TYPE_3__* out; scalar_t__ start_chunk; } ;
typedef  TYPE_6__ ngx_http_mp4_trak_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; TYPE_1__ name; } ;
struct TYPE_19__ {TYPE_2__ file; } ;
typedef  TYPE_7__ ngx_http_mp4_file_t ;
struct TYPE_20__ {scalar_t__ pos; scalar_t__ last; } ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_15__ {TYPE_8__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_MP4_STSC_ATOM ; 
 size_t NGX_HTTP_MP4_STSC_DATA ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_mp4_crop_stsc_data (TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t ngx_mp4_get_32value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mp4_set_32value (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_update_stsc_atom(ngx_http_mp4_file_t *mp4,
    ngx_http_mp4_trak_t *trak)
{
    size_t                 atom_size;
    uint32_t               chunk;
    ngx_buf_t             *atom, *data;
    ngx_mp4_stsc_atom_t   *stsc_atom;
    ngx_mp4_stsc_entry_t  *entry, *end;

    /*
     * mdia.minf.stbl.stsc updating requires trak->start_sample
     * from mdia.minf.stbl.stts which depends on value from mdia.mdhd
     * atom which may reside after mdia.minf
     */

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 stsc atom update");

    data = trak->out[NGX_HTTP_MP4_STSC_DATA].buf;

    if (data == NULL) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "no mp4 stsc atoms were found in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    if (trak->sample_to_chunk_entries == 0) {
        ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                      "zero number of entries in stsc atom in \"%s\"",
                      mp4->file.name.data);
        return NGX_ERROR;
    }

    if (ngx_http_mp4_crop_stsc_data(mp4, trak, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    if (ngx_http_mp4_crop_stsc_data(mp4, trak, 0) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "sample-to-chunk entries:%uD",
                   trak->sample_to_chunk_entries);

    entry = (ngx_mp4_stsc_entry_t *) data->pos;
    end = (ngx_mp4_stsc_entry_t *) data->last;

    while (entry < end) {
        chunk = ngx_mp4_get_32value(entry->chunk);
        chunk -= trak->start_chunk;
        ngx_mp4_set_32value(entry->chunk, chunk);
        entry++;
    }

    atom_size = sizeof(ngx_mp4_stsc_atom_t)
                + trak->sample_to_chunk_entries * sizeof(ngx_mp4_stsc_entry_t);

    trak->size += atom_size;

    atom = trak->out[NGX_HTTP_MP4_STSC_ATOM].buf;
    stsc_atom = (ngx_mp4_stsc_atom_t *) atom->pos;

    ngx_mp4_set_32value(stsc_atom->size, atom_size);
    ngx_mp4_set_32value(stsc_atom->entries, trak->sample_to_chunk_entries);

    return NGX_OK;
}