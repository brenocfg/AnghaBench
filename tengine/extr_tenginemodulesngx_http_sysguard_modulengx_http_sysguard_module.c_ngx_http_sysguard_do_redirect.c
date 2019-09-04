#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/  args; } ;
typedef  TYPE_2__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_SERVICE_UNAVAILABLE ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_internal_redirect (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_named_location (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_sysguard_do_redirect(ngx_http_request_t *r, ngx_str_t *path)
{
    if (path->len == 0) {
        return NGX_HTTP_SERVICE_UNAVAILABLE;
    } else if (path->data[0] == '@') {
        (void) ngx_http_named_location(r, path);
    } else {
        (void) ngx_http_internal_redirect(r, path, &r->args);
    }

    ngx_http_finalize_request(r, NGX_DONE);

    return NGX_DONE;
}