#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ conf_prefix; } ;
typedef  TYPE_3__ ngx_http_script_full_name_code_t ;
struct TYPE_10__ {scalar_t__ ip; } ;
typedef  TYPE_4__ ngx_http_script_engine_t ;
struct TYPE_8__ {size_t len; } ;
struct TYPE_7__ {size_t len; } ;
struct TYPE_11__ {TYPE_2__ prefix; TYPE_1__ conf_prefix; } ;

/* Variables and functions */
 TYPE_6__* ngx_cycle ; 

__attribute__((used)) static size_t
ngx_http_script_full_name_len_code(ngx_http_script_engine_t *e)
{
    ngx_http_script_full_name_code_t  *code;

    code = (ngx_http_script_full_name_code_t *) e->ip;

    e->ip += sizeof(ngx_http_script_full_name_code_t);

    return code->conf_prefix ? ngx_cycle->conf_prefix.len:
                               ngx_cycle->prefix.len;
}