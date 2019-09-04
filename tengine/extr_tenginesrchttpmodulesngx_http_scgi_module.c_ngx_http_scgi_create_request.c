#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_20__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_19__ ;
typedef  struct TYPE_38__   TYPE_18__ ;
typedef  struct TYPE_37__   TYPE_17__ ;
typedef  struct TYPE_36__   TYPE_16__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ off_t ;
typedef  int ngx_uint_t ;
struct TYPE_46__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_45__ {size_t len; char* data; } ;
struct TYPE_32__ {TYPE_6__ value; TYPE_5__ key; } ;
typedef  TYPE_10__ ngx_table_elt_t ;
struct TYPE_33__ {char* data; int len; } ;
typedef  TYPE_11__ ngx_str_t ;
struct TYPE_34__ {int nelts; TYPE_10__* elts; struct TYPE_34__* next; } ;
typedef  TYPE_12__ ngx_list_part_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  size_t (* ngx_http_script_len_code_pt ) (TYPE_13__*) ;
struct TYPE_35__ {int flushed; char* pos; int skip; scalar_t__ ip; TYPE_18__* request; } ;
typedef  TYPE_13__ ngx_http_script_engine_t ;
typedef  int /*<<< orphan*/  (* ngx_http_script_code_pt ) (TYPE_13__*) ;
struct TYPE_36__ {TYPE_2__* lengths; TYPE_1__* values; int /*<<< orphan*/  hash; scalar_t__ number; int /*<<< orphan*/  flushes; } ;
typedef  TYPE_16__ ngx_http_scgi_params_t ;
struct TYPE_48__ {scalar_t__ pass_request_body; scalar_t__ pass_request_headers; } ;
struct TYPE_37__ {TYPE_8__ upstream; TYPE_16__ params; } ;
typedef  TYPE_17__ ngx_http_scgi_loc_conf_t ;
struct TYPE_43__ {TYPE_12__ part; } ;
struct TYPE_44__ {TYPE_3__ headers; } ;
struct TYPE_38__ {TYPE_9__* upstream; int /*<<< orphan*/  pool; scalar_t__ request_body_no_buffering; TYPE_7__* connection; TYPE_4__ headers_in; } ;
typedef  TYPE_18__ ngx_http_request_t ;
struct TYPE_39__ {struct TYPE_39__* next; TYPE_20__* buf; } ;
typedef  TYPE_19__ ngx_chain_t ;
struct TYPE_41__ {char* last; } ;
typedef  TYPE_20__ ngx_buf_t ;
struct TYPE_49__ {TYPE_19__* request_bufs; } ;
struct TYPE_47__ {int /*<<< orphan*/  log; } ;
struct TYPE_42__ {scalar_t__ elts; } ;
struct TYPE_40__ {scalar_t__ elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_OFF_T_LEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_SIZE_T_LEN ; 
 TYPE_20__* ngx_alloc_buf (int /*<<< orphan*/ ) ; 
 void* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_buf_size (TYPE_20__*) ; 
 char* ngx_copy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* ngx_cpymem (char*,char*,int) ; 
 TYPE_20__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int ngx_hash (int,char) ; 
 scalar_t__ ngx_hash_find (int /*<<< orphan*/ *,int,char*,int) ; 
 TYPE_17__* ngx_http_get_module_loc_conf (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_scgi_module ; 
 int /*<<< orphan*/  ngx_http_script_flush_no_cacheable_variables (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_20__*,TYPE_20__*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_13__*,int) ; 
 TYPE_10__** ngx_palloc (int /*<<< orphan*/ ,int) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 char* ngx_sprintf (char*,char*,size_t,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_scgi_create_request(ngx_http_request_t *r)
{
    off_t                         content_length_n;
    u_char                        ch, *key, *val, *lowcase_key;
    size_t                        len, key_len, val_len, allocated;
    ngx_buf_t                    *b;
    ngx_str_t                     content_length;
    ngx_uint_t                    i, n, hash, skip_empty, header_params;
    ngx_chain_t                  *cl, *body;
    ngx_list_part_t              *part;
    ngx_table_elt_t              *header, **ignored;
    ngx_http_scgi_params_t       *params;
    ngx_http_script_code_pt       code;
    ngx_http_script_engine_t      e, le;
    ngx_http_scgi_loc_conf_t     *scf;
    ngx_http_script_len_code_pt   lcode;
    u_char                        buffer[NGX_OFF_T_LEN];

    content_length_n = 0;
    body = r->upstream->request_bufs;

    while (body) {
        content_length_n += ngx_buf_size(body->buf);
        body = body->next;
    }

    content_length.data = buffer;
    content_length.len = ngx_sprintf(buffer, "%O", content_length_n) - buffer;

    len = sizeof("CONTENT_LENGTH") + content_length.len + 1;

    header_params = 0;
    ignored = NULL;

    scf = ngx_http_get_module_loc_conf(r, ngx_http_scgi_module);

#if (NGX_HTTP_CACHE)
    params = r->upstream->cacheable ? &scf->params_cache : &scf->params;
#else
    params = &scf->params;
#endif

    if (params->lengths) {
        ngx_memzero(&le, sizeof(ngx_http_script_engine_t));

        ngx_http_script_flush_no_cacheable_variables(r, params->flushes);
        le.flushed = 1;

        le.ip = params->lengths->elts;
        le.request = r;

        while (*(uintptr_t *) le.ip) {

            lcode = *(ngx_http_script_len_code_pt *) le.ip;
            key_len = lcode(&le);

            lcode = *(ngx_http_script_len_code_pt *) le.ip;
            skip_empty = lcode(&le);

            for (val_len = 0; *(uintptr_t *) le.ip; val_len += lcode(&le)) {
                lcode = *(ngx_http_script_len_code_pt *) le.ip;
            }
            le.ip += sizeof(uintptr_t);

            if (skip_empty && val_len == 0) {
                continue;
            }

            len += key_len + val_len + 1;
        }
    }

    if (scf->upstream.pass_request_headers) {

        allocated = 0;
        lowcase_key = NULL;

        if (params->number) {
            n = 0;
            part = &r->headers_in.headers.part;

            while (part) {
                n += part->nelts;
                part = part->next;
            }

            ignored = ngx_palloc(r->pool, n * sizeof(void *));
            if (ignored == NULL) {
                return NGX_ERROR;
            }
        }

        part = &r->headers_in.headers.part;
        header = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                header = part->elts;
                i = 0;
            }

            if (params->number) {
                if (allocated < header[i].key.len) {
                    allocated = header[i].key.len + 16;
                    lowcase_key = ngx_pnalloc(r->pool, allocated);
                    if (lowcase_key == NULL) {
                        return NGX_ERROR;
                    }
                }

                hash = 0;

                for (n = 0; n < header[i].key.len; n++) {
                    ch = header[i].key.data[n];

                    if (ch >= 'A' && ch <= 'Z') {
                        ch |= 0x20;

                    } else if (ch == '-') {
                        ch = '_';
                    }

                    hash = ngx_hash(hash, ch);
                    lowcase_key[n] = ch;
                }

                if (ngx_hash_find(&params->hash, hash, lowcase_key, n)) {
                    ignored[header_params++] = &header[i];
                    continue;
                }
            }

            len += sizeof("HTTP_") - 1 + header[i].key.len + 1
                + header[i].value.len + 1;
        }
    }

    /* netstring: "length:" + packet + "," */

    b = ngx_create_temp_buf(r->pool, NGX_SIZE_T_LEN + 1 + len + 1);
    if (b == NULL) {
        return NGX_ERROR;
    }

    cl = ngx_alloc_chain_link(r->pool);
    if (cl == NULL) {
        return NGX_ERROR;
    }

    cl->buf = b;

    b->last = ngx_sprintf(b->last, "%ui:CONTENT_LENGTH%Z%V%Z",
                          len, &content_length);

    if (params->lengths) {
        ngx_memzero(&e, sizeof(ngx_http_script_engine_t));

        e.ip = params->values->elts;
        e.pos = b->last;
        e.request = r;
        e.flushed = 1;

        le.ip = params->lengths->elts;

        while (*(uintptr_t *) le.ip) {

            lcode = *(ngx_http_script_len_code_pt *) le.ip;
            lcode(&le); /* key length */

            lcode = *(ngx_http_script_len_code_pt *) le.ip;
            skip_empty = lcode(&le);

            for (val_len = 0; *(uintptr_t *) le.ip; val_len += lcode(&le)) {
                lcode = *(ngx_http_script_len_code_pt *) le.ip;
            }
            le.ip += sizeof(uintptr_t);

            if (skip_empty && val_len == 0) {
                e.skip = 1;

                while (*(uintptr_t *) e.ip) {
                    code = *(ngx_http_script_code_pt *) e.ip;
                    code((ngx_http_script_engine_t *) &e);
                }
                e.ip += sizeof(uintptr_t);

                e.skip = 0;

                continue;
            }

#if (NGX_DEBUG)
            key = e.pos;
#endif
            code = *(ngx_http_script_code_pt *) e.ip;
            code((ngx_http_script_engine_t *) &e);

#if (NGX_DEBUG)
            val = e.pos;
#endif
            while (*(uintptr_t *) e.ip) {
                code = *(ngx_http_script_code_pt *) e.ip;
                code((ngx_http_script_engine_t *) &e);
            }
            *e.pos++ = '\0';
            e.ip += sizeof(uintptr_t);

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "scgi param: \"%s: %s\"", key, val);
        }

        b->last = e.pos;
    }

    if (scf->upstream.pass_request_headers) {

        part = &r->headers_in.headers.part;
        header = part->elts;

        for (i = 0; /* void */; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                header = part->elts;
                i = 0;
            }

            for (n = 0; n < header_params; n++) {
                if (&header[i] == ignored[n]) {
                    goto next;
                }
            }

            key = b->last;
            b->last = ngx_cpymem(key, "HTTP_", sizeof("HTTP_") - 1);

            for (n = 0; n < header[i].key.len; n++) {
                ch = header[i].key.data[n];

                if (ch >= 'a' && ch <= 'z') {
                    ch &= ~0x20;

                } else if (ch == '-') {
                    ch = '_';
                }

                *b->last++ = ch;
            }

            *b->last++ = (u_char) 0;

            val = b->last;
            b->last = ngx_copy(val, header[i].value.data, header[i].value.len);
            *b->last++ = (u_char) 0;

            ngx_log_debug2(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "scgi param: \"%s: %s\"", key, val);

        next:

            continue;
        }
    }

    *b->last++ = (u_char) ',';

    if (r->request_body_no_buffering) {
        r->upstream->request_bufs = cl;

    } else if (scf->upstream.pass_request_body) {
        body = r->upstream->request_bufs;
        r->upstream->request_bufs = cl;

        while (body) {
            b = ngx_alloc_buf(r->pool);
            if (b == NULL) {
                return NGX_ERROR;
            }

            ngx_memcpy(b, body->buf, sizeof(ngx_buf_t));

            cl->next = ngx_alloc_chain_link(r->pool);
            if (cl->next == NULL) {
                return NGX_ERROR;
            }

            cl = cl->next;
            cl->buf = b;

            body = body->next;
        }

    } else {
        r->upstream->request_bufs = cl;
    }

    cl->next = NULL;

    return NGX_OK;
}