#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {scalar_t__ len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {size_t captures_mask; int dup_capture; int args; int /*<<< orphan*/  cf; TYPE_1__* source; int /*<<< orphan*/  size; scalar_t__ compile_args; int /*<<< orphan*/  variables; } ;
typedef  TYPE_3__ ngx_http_script_compile_t ;
struct TYPE_13__ {size_t len; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_http_script_add_args_code (TYPE_3__*) ; 
 scalar_t__ ngx_http_script_add_capture_code (TYPE_3__*,size_t) ; 
 scalar_t__ ngx_http_script_add_copy_code (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ ngx_http_script_add_var_code (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_http_script_done (TYPE_3__*) ; 
 scalar_t__ ngx_http_script_init_arrays (TYPE_3__*) ; 

ngx_int_t
ngx_http_script_compile(ngx_http_script_compile_t *sc)
{
    u_char       ch;
    ngx_str_t    name;
    ngx_uint_t   i, bracket;

    if (ngx_http_script_init_arrays(sc) != NGX_OK) {
        return NGX_ERROR;
    }

    for (i = 0; i < sc->source->len; /* void */ ) {

        name.len = 0;

        if (sc->source->data[i] == '$') {

            if (++i == sc->source->len) {
                goto invalid_variable;
            }

            if (sc->source->data[i] >= '1' && sc->source->data[i] <= '9') {
#if (NGX_PCRE)
                ngx_uint_t  n;

                n = sc->source->data[i] - '0';

                if (sc->captures_mask & ((ngx_uint_t) 1 << n)) {
                    sc->dup_capture = 1;
                }

                sc->captures_mask |= (ngx_uint_t) 1 << n;

                if (ngx_http_script_add_capture_code(sc, n) != NGX_OK) {
                    return NGX_ERROR;
                }

                i++;

                continue;
#else
                ngx_conf_log_error(NGX_LOG_EMERG, sc->cf, 0,
                                   "using variable \"$%c\" requires "
                                   "PCRE library", sc->source->data[i]);
                return NGX_ERROR;
#endif
            }

            if (sc->source->data[i] == '{') {
                bracket = 1;

                if (++i == sc->source->len) {
                    goto invalid_variable;
                }

                name.data = &sc->source->data[i];

            } else {
                bracket = 0;
                name.data = &sc->source->data[i];
            }

            for ( /* void */ ; i < sc->source->len; i++, name.len++) {
                ch = sc->source->data[i];

                if (ch == '}' && bracket) {
                    i++;
                    bracket = 0;
                    break;
                }

                if ((ch >= 'A' && ch <= 'Z')
                    || (ch >= 'a' && ch <= 'z')
                    || (ch >= '0' && ch <= '9')
                    || ch == '_')
                {
                    continue;
                }

                break;
            }

            if (bracket) {
                ngx_conf_log_error(NGX_LOG_EMERG, sc->cf, 0,
                                   "the closing bracket in \"%V\" "
                                   "variable is missing", &name);
                return NGX_ERROR;
            }

            if (name.len == 0) {
                goto invalid_variable;
            }

            sc->variables++;

            if (ngx_http_script_add_var_code(sc, &name) != NGX_OK) {
                return NGX_ERROR;
            }

            continue;
        }

        if (sc->source->data[i] == '?' && sc->compile_args) {
            sc->args = 1;
            sc->compile_args = 0;

            if (ngx_http_script_add_args_code(sc) != NGX_OK) {
                return NGX_ERROR;
            }

            i++;

            continue;
        }

        name.data = &sc->source->data[i];

        while (i < sc->source->len) {

            if (sc->source->data[i] == '$') {
                break;
            }

            if (sc->source->data[i] == '?') {

                sc->args = 1;

                if (sc->compile_args) {
                    break;
                }
            }

            i++;
            name.len++;
        }

        sc->size += name.len;

        if (ngx_http_script_add_copy_code(sc, &name, (i == sc->source->len))
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    return ngx_http_script_done(sc);

invalid_variable:

    ngx_conf_log_error(NGX_LOG_EMERG, sc->cf, 0, "invalid variable name");

    return NGX_ERROR;
}