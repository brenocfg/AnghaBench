#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {char* data; size_t len; } ;
struct TYPE_13__ {int len; char* data; } ;
struct TYPE_15__ {scalar_t__ hash; TYPE_4__ value; TYPE_3__ key; } ;
typedef  TYPE_5__ ngx_table_elt_t ;
struct TYPE_16__ {int len; char* data; } ;
typedef  TYPE_6__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_md5_t ;
struct TYPE_17__ {size_t nelts; TYPE_5__* elts; struct TYPE_17__* next; } ;
typedef  TYPE_7__ ngx_list_part_t ;
struct TYPE_11__ {TYPE_7__ part; } ;
struct TYPE_12__ {TYPE_1__ headers; } ;
struct TYPE_18__ {TYPE_2__ headers_in; } ;
typedef  TYPE_8__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_md5_update (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ ngx_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static void
ngx_http_file_cache_vary_header(ngx_http_request_t *r, ngx_md5_t *md5,
    ngx_str_t *name)
{
    size_t            len;
    u_char           *p, *start, *last;
    ngx_uint_t        i, multiple, normalize;
    ngx_list_part_t  *part;
    ngx_table_elt_t  *header;

    multiple = 0;
    normalize = 0;

    if (name->len == sizeof("Accept-Charset") - 1
        && ngx_strncasecmp(name->data, (u_char *) "Accept-Charset",
                           sizeof("Accept-Charset") - 1) == 0)
    {
        normalize = 1;

    } else if (name->len == sizeof("Accept-Encoding") - 1
        && ngx_strncasecmp(name->data, (u_char *) "Accept-Encoding",
                           sizeof("Accept-Encoding") - 1) == 0)
    {
        normalize = 1;

    } else if (name->len == sizeof("Accept-Language") - 1
        && ngx_strncasecmp(name->data, (u_char *) "Accept-Language",
                           sizeof("Accept-Language") - 1) == 0)
    {
        normalize = 1;
    }

    part = &r->headers_in.headers.part;
    header = part->elts;

    for (i = 0; /* void */ ; i++) {

        if (i >= part->nelts) {
            if (part->next == NULL) {
                break;
            }

            part = part->next;
            header = part->elts;
            i = 0;
        }

        if (header[i].hash == 0) {
            continue;
        }

        if (header[i].key.len != name->len) {
            continue;
        }

        if (ngx_strncasecmp(header[i].key.data, name->data, name->len) != 0) {
            continue;
        }

        if (!normalize) {

            if (multiple) {
                ngx_md5_update(md5, (u_char *) ",", sizeof(",") - 1);
            }

            ngx_md5_update(md5, header[i].value.data, header[i].value.len);

            multiple = 1;

            continue;
        }

        /* normalize spaces */

        p = header[i].value.data;
        last = p + header[i].value.len;

        while (p < last) {

            while (p < last && (*p == ' ' || *p == ',')) { p++; }

            start = p;

            while (p < last && *p != ',' && *p != ' ') { p++; }

            len = p - start;

            if (len == 0) {
                break;
            }

            if (multiple) {
                ngx_md5_update(md5, (u_char *) ",", sizeof(",") - 1);
            }

            ngx_md5_update(md5, start, len);

            multiple = 1;
        }
    }
}