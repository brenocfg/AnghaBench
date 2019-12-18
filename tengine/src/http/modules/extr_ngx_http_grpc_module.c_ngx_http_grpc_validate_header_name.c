#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_3__ {size_t len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 char CR ; 
 char LF ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_grpc_validate_header_name(ngx_http_request_t *r, ngx_str_t *s)
{
    u_char      ch;
    ngx_uint_t  i;

    for (i = 0; i < s->len; i++) {
        ch = s->data[i];

        if (ch == ':' && i > 0) {
            return NGX_ERROR;
        }

        if (ch >= 'A' && ch <= 'Z') {
            return NGX_ERROR;
        }

        if (ch == '\0' || ch == CR || ch == LF) {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}