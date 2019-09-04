#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  ngx_mp4_atom_header_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {int temporary; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; } ;
struct TYPE_15__ {TYPE_1__* out; TYPE_5__ trak_atom_buf; } ;
typedef  TYPE_3__ ngx_http_mp4_trak_t ;
struct TYPE_12__ {int /*<<< orphan*/  nelts; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {scalar_t__ offset; int /*<<< orphan*/ * buffer_pos; TYPE_11__ trak; TYPE_2__ file; } ;
typedef  TYPE_4__ ngx_http_mp4_file_t ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_13__ {TYPE_5__* buf; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 size_t NGX_HTTP_MP4_TRAK_ATOM ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 TYPE_3__* ngx_array_push (TYPE_11__*) ; 
 scalar_t__ ngx_http_mp4_read_atom (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_mp4_trak_atoms ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * ngx_mp4_atom_header (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_mp4_set_atom_name (int /*<<< orphan*/ *,char,char,char,char) ; 

__attribute__((used)) static ngx_int_t
ngx_http_mp4_read_trak_atom(ngx_http_mp4_file_t *mp4, uint64_t atom_data_size)
{
    u_char               *atom_header, *atom_end;
    off_t                 atom_file_end;
    ngx_int_t             rc;
    ngx_buf_t            *atom;
    ngx_http_mp4_trak_t  *trak;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0, "mp4 trak atom");

    trak = ngx_array_push(&mp4->trak);
    if (trak == NULL) {
        return NGX_ERROR;
    }

    ngx_memzero(trak, sizeof(ngx_http_mp4_trak_t));

    atom_header = ngx_mp4_atom_header(mp4);
    ngx_mp4_set_atom_name(atom_header, 't', 'r', 'a', 'k');

    atom = &trak->trak_atom_buf;
    atom->temporary = 1;
    atom->pos = atom_header;
    atom->last = atom_header + sizeof(ngx_mp4_atom_header_t);

    trak->out[NGX_HTTP_MP4_TRAK_ATOM].buf = atom;

    atom_end = mp4->buffer_pos + (size_t) atom_data_size;
    atom_file_end = mp4->offset + atom_data_size;

    rc = ngx_http_mp4_read_atom(mp4, ngx_http_mp4_trak_atoms, atom_data_size);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, mp4->file.log, 0,
                   "mp4 trak atom: %i", rc);

    if (rc == NGX_DECLINED) {
        /* skip this trak */
        ngx_memzero(trak, sizeof(ngx_http_mp4_trak_t));
        mp4->trak.nelts--;
        mp4->buffer_pos = atom_end;
        mp4->offset = atom_file_end;
        return NGX_OK;
    }

    return rc;
}