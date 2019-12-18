#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* str; char* ptr; } ;
struct TYPE_4__ {char* ptr; char* str; } ;
struct TYPE_6__ {int sent_begin; size_t begin_code_len; scalar_t__ file_type; char const* buff; int sent_end; size_t end_code_len; scalar_t__ rest_len; TYPE_2__ end_code; int /*<<< orphan*/  f; TYPE_1__ begin_code; scalar_t__ extraline; } ;
typedef  TYPE_3__ ngx_http_lua_clfactory_file_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ NGX_LUA_BT_LJ ; 
 scalar_t__ NGX_LUA_BT_LUA ; 
 scalar_t__ NGX_LUA_TEXT_FILE ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 size_t fread (char const*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
ngx_http_lua_clfactory_getF(lua_State *L, void *ud, size_t *size)
{
#ifndef OPENRESTY_LUAJIT
    char                        *buf;
#endif
    size_t                       num;

    ngx_http_lua_clfactory_file_ctx_t        *lf;

    lf = (ngx_http_lua_clfactory_file_ctx_t *) ud;

    if (lf->extraline) {
        lf->extraline = 0;
        *size = 1;
        return "\n";
    }

#ifndef OPENRESTY_LUAJIT
    if (lf->sent_begin == 0) {
        lf->sent_begin = 1;
        *size = lf->begin_code_len;

        if (lf->file_type == NGX_LUA_TEXT_FILE) {
            buf = lf->begin_code.ptr;

        } else {
            buf = lf->begin_code.str;
        }

        return buf;
    }
#endif /* OPENRESTY_LUAJIT */

    num = fread(lf->buff, 1, sizeof(lf->buff), lf->f);

    dd("fread returned %d", (int) num);

    if (num == 0) {
#ifndef OPENRESTY_LUAJIT
        if (lf->sent_end == 0) {
            lf->sent_end = 1;
            *size = lf->end_code_len;

            if (lf->file_type == NGX_LUA_BT_LUA) {
                buf = lf->end_code.str;

            } else {
                buf = lf->end_code.ptr;
            }

            return buf;
        }
#endif /* OPENRESTY_LUAJIT */

        *size = 0;
        return NULL;
    }

#ifndef OPENRESTY_LUAJIT
    if (lf->file_type == NGX_LUA_BT_LJ) {
        /* skip the footer(\x00) in luajit */

        lf->rest_len -= num;

        if (lf->rest_len == 0) {
            if (--num == 0 && lf->sent_end == 0) {
                lf->sent_end = 1;
                buf = lf->end_code.ptr;
                *size = lf->end_code_len;

                return buf;
            }
        }
    }
#endif /* OPENRESTY_LUAJIT */

    *size = num;
    return lf->buff;
}