#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_9__ {scalar_t__ len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int msie6; int opera; int gecko; int chrome; int safari; int konqueror; int /*<<< orphan*/  msie; } ;
struct TYPE_10__ {TYPE_1__ headers_in; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_header_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_set_builtin_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* ngx_strstrn (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_user_agent_header(ngx_http_request_t *r,
    ngx_http_lua_header_val_t *hv, ngx_str_t *value)
{
    u_char  *user_agent, *msie;

    /* clear existing settings */

    r->headers_in.msie = 0;
    r->headers_in.msie6 = 0;
    r->headers_in.opera = 0;
    r->headers_in.gecko = 0;
    r->headers_in.chrome = 0;
    r->headers_in.safari = 0;
    r->headers_in.konqueror = 0;

    if (value->len == 0) {
        return ngx_http_set_builtin_header(r, hv, value);
    }

    /* check some widespread browsers */

    user_agent = value->data;

    msie = ngx_strstrn(user_agent, "MSIE ", 5 - 1);

    if (msie && msie + 7 < user_agent + value->len) {

        r->headers_in.msie = 1;

        if (msie[6] == '.') {

            switch (msie[5]) {
            case '4':
            case '5':
                r->headers_in.msie6 = 1;
                break;
            case '6':
                if (ngx_strstrn(msie + 8, "SV1", 3 - 1) == NULL) {
                    r->headers_in.msie6 = 1;
                }
                break;
            }
        }
    }

    if (ngx_strstrn(user_agent, "Opera", 5 - 1)) {
        r->headers_in.opera = 1;
        r->headers_in.msie = 0;
        r->headers_in.msie6 = 0;
    }

    if (!r->headers_in.msie && !r->headers_in.opera) {

        if (ngx_strstrn(user_agent, "Gecko/", 6 - 1)) {
            r->headers_in.gecko = 1;

        } else if (ngx_strstrn(user_agent, "Chrome/", 7 - 1)) {
            r->headers_in.chrome = 1;

        } else if (ngx_strstrn(user_agent, "Safari/", 7 - 1)
                   && ngx_strstrn(user_agent, "Mac OS X", 8 - 1))
        {
            r->headers_in.safari = 1;

        } else if (ngx_strstrn(user_agent, "Konqueror", 9 - 1)) {
            r->headers_in.konqueror = 1;
        }
    }

    return ngx_http_set_builtin_header(r, hv, value);
}