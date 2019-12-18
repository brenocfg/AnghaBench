#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_mp4_trak_t ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  log; TYPE_2__ name; } ;
struct TYPE_22__ {int temporary; scalar_t__ last; scalar_t__ pos; } ;
struct TYPE_18__ {TYPE_8__* buf; } ;
struct TYPE_17__ {int size; int nalloc; int /*<<< orphan*/  pool; int /*<<< orphan*/ * elts; } ;
struct TYPE_15__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_20__ {scalar_t__ start; scalar_t__ length; scalar_t__ buffer_size; int /*<<< orphan*/  end; int /*<<< orphan*/  offset; int /*<<< orphan*/ * buffer_end; int /*<<< orphan*/ * buffer_pos; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * buffer_start; TYPE_5__ file; TYPE_8__ moov_atom_buf; TYPE_4__ moov_atom; scalar_t__ moov_atom_header; TYPE_13__* request; TYPE_3__ trak; int /*<<< orphan*/  traks; TYPE_1__ mdat_atom; } ;
typedef  TYPE_6__ ngx_http_mp4_file_t ;
struct TYPE_21__ {scalar_t__ max_buffer_size; } ;
typedef  TYPE_7__ ngx_http_mp4_conf_t ;
typedef  TYPE_8__ ngx_buf_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 size_t NGX_HTTP_MP4_MOOV_BUFFER_EXCESS ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 TYPE_7__* ngx_http_get_module_loc_conf (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_mp4_module ; 
 int /*<<< orphan*/  ngx_http_mp4_moov_atoms ; 
 scalar_t__ ngx_http_mp4_read (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  ngx_http_mp4_read_atom (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_read_moov_atom(ngx_http_mp4_file_t *mp4, uint64_t atom_data_size)
{
    ngx_int_t             rc;
    ngx_uint_t            no_mdat;
    ngx_buf_t            *atom;
    ngx_http_mp4_conf_t  *conf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0, "mp4 moov atom");

    no_mdat = (mp4->mdat_atom.buf == NULL);

    if (no_mdat && mp4->start == 0 && mp4->length == 0) {
        /*
         * send original file if moov atom resides before
         * mdat atom and client requests integral file
         */
        return NGX_DECLINED;
    }

    conf = ngx_http_get_module_loc_conf(mp4->request, ngx_http_mp4_module);

    if (atom_data_size > mp4->buffer_size) {

        if (atom_data_size > conf->max_buffer_size) {
            ngx_log_error(NGX_LOG_ERR, mp4->file.log, 0,
                          "\"%s\" mp4 moov atom is too large:%uL, "
                          "you may want to increase mp4_max_buffer_size",
                          mp4->file.name.data, atom_data_size);
            return NGX_ERROR;
        }

        ngx_pfree(mp4->request->pool, mp4->buffer);
        mp4->buffer = NULL;
        mp4->buffer_pos = NULL;
        mp4->buffer_end = NULL;

        mp4->buffer_size = (size_t) atom_data_size
                         + NGX_HTTP_MP4_MOOV_BUFFER_EXCESS * no_mdat;
    }

    if (ngx_http_mp4_read(mp4, (size_t) atom_data_size) != NGX_OK) {
        return NGX_ERROR;
    }

    mp4->trak.elts = &mp4->traks;
    mp4->trak.size = sizeof(ngx_http_mp4_trak_t);
    mp4->trak.nalloc = 2;
    mp4->trak.pool = mp4->request->pool;

    atom = &mp4->moov_atom_buf;
    atom->temporary = 1;
    atom->pos = mp4->moov_atom_header;
    atom->last = mp4->moov_atom_header + 8;

    mp4->moov_atom.buf = &mp4->moov_atom_buf;

    rc = ngx_http_mp4_read_atom(mp4, ngx_http_mp4_moov_atoms, atom_data_size);

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0, "mp4 moov atom done");

    if (no_mdat) {
        mp4->buffer_start = mp4->buffer_pos;
        mp4->buffer_size = NGX_HTTP_MP4_MOOV_BUFFER_EXCESS;

        if (mp4->buffer_start + mp4->buffer_size > mp4->buffer_end) {
            mp4->buffer = NULL;
            mp4->buffer_pos = NULL;
            mp4->buffer_end = NULL;
        }

    } else {
        /* skip atoms after moov atom */
        mp4->offset = mp4->end;
    }

    return rc;
}