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
struct TYPE_3__ {uintptr_t len; int escape; int /*<<< orphan*/  data; scalar_t__ not_found; } ;
typedef  TYPE_1__ ngx_stream_variable_value_t ;
typedef  int /*<<< orphan*/  ngx_stream_session_t ;

/* Variables and functions */
 TYPE_1__* ngx_stream_get_indexed_variable (int /*<<< orphan*/ *,uintptr_t) ; 
 uintptr_t ngx_stream_log_escape (int /*<<< orphan*/ *,int /*<<< orphan*/ ,uintptr_t) ; 

__attribute__((used)) static size_t
ngx_stream_log_variable_getlen(ngx_stream_session_t *s, uintptr_t data)
{
    uintptr_t                     len;
    ngx_stream_variable_value_t  *value;

    value = ngx_stream_get_indexed_variable(s, data);

    if (value == NULL || value->not_found) {
        return 1;
    }

    len = ngx_stream_log_escape(NULL, value->data, value->len);

    value->escape = len ? 1 : 0;

    return value->len + len * 3;
}