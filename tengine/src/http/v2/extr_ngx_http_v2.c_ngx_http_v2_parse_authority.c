#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_v2_parse_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_parse_headers ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_parse_authority(ngx_http_request_t *r, ngx_str_t *value)
{
    return ngx_http_v2_parse_header(r, &ngx_http_v2_parse_headers[0], value);
}