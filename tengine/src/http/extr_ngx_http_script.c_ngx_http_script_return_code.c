#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_9__ {scalar_t__ lengths; TYPE_1__ value; } ;
struct TYPE_7__ {scalar_t__ status; TYPE_4__ text; } ;
typedef  TYPE_2__ ngx_http_script_return_code_t ;
struct TYPE_8__ {scalar_t__ status; scalar_t__ ip; int /*<<< orphan*/  request; } ;
typedef  TYPE_3__ ngx_http_script_engine_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_BAD_REQUEST ; 
 scalar_t__ ngx_http_script_exit ; 
 scalar_t__ ngx_http_send_response (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,TYPE_4__*) ; 

void
ngx_http_script_return_code(ngx_http_script_engine_t *e)
{
    ngx_http_script_return_code_t  *code;

    code = (ngx_http_script_return_code_t *) e->ip;

    if (code->status < NGX_HTTP_BAD_REQUEST
        || code->text.value.len
        || code->text.lengths)
    {
        e->status = ngx_http_send_response(e->request, code->status, NULL,
                                           &code->text);
    } else {
        e->status = code->status;
    }

    e->ip = ngx_http_script_exit;
}