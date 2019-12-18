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
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_10__ {size_t len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {TYPE_1__* source; int /*<<< orphan*/  log; int /*<<< orphan*/  variables; } ;
typedef  TYPE_2__ ngx_http_lua_script_compile_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_lua_script_add_capture_code (TYPE_2__*,size_t) ; 
 scalar_t__ ngx_http_lua_script_add_copy_code (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_script_done (TYPE_2__*) ; 
 scalar_t__ ngx_http_lua_script_init_arrays (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_script_compile(ngx_http_lua_script_compile_t *sc)
{
    u_char       ch;
    ngx_str_t    name;
    ngx_uint_t   i, bracket;
    unsigned     num_var;
    ngx_uint_t   n = 0;

    if (ngx_http_lua_script_init_arrays(sc) != NGX_OK) {
        return NGX_ERROR;
    }

    for (i = 0; i < sc->source->len; /* void */ ) {

        name.len = 0;

        if (sc->source->data[i] == '$') {

            if (++i == sc->source->len) {
                goto invalid_variable;
            }

            if (sc->source->data[i] == '$') {
                name.data = &sc->source->data[i];
                i++;
                name.len++;

                if (ngx_http_lua_script_add_copy_code(sc, &name,
                                                      (i == sc->source->len))
                    != NGX_OK)
                {
                    return NGX_ERROR;
                }

                continue;
            }

            if (sc->source->data[i] >= '0' && sc->source->data[i] <= '9') {
                num_var = 1;
                n = 0;

            } else {
                num_var = 0;
            }

            if (sc->source->data[i] == '{') {
                bracket = 1;

                if (++i == sc->source->len) {
                    goto invalid_variable;
                }

                if (sc->source->data[i] >= '0' && sc->source->data[i] <= '9') {
                    num_var = 1;
                    n = 0;
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

                if (num_var) {
                    if (ch >= '0' && ch <= '9') {
                        n = n * 10 + (ch - '0');
                        continue;
                    }

                    break;
                }

                /* not a number variable like $1, $2, etc */

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
                ngx_log_error(NGX_LOG_ERR, sc->log, 0,
                              "the closing bracket in \"%V\" "
                              "variable is missing", &name);
                return NGX_ERROR;
            }

            if (name.len == 0) {
                goto invalid_variable;
            }

            if (!num_var) {
                ngx_log_error(NGX_LOG_ERR, sc->log, 0,
                              "attempt to use named capturing variable "
                              "\"%V\" (named captures not supported yet)",
                              &name);

                return NGX_ERROR;
            }

            sc->variables++;

            if (ngx_http_lua_script_add_capture_code(sc, n) != NGX_OK) {
                return NGX_ERROR;
            }

            continue;
        }

        name.data = &sc->source->data[i];

        while (i < sc->source->len) {

            if (sc->source->data[i] == '$') {
                break;
            }

            i++;
            name.len++;
        }

        if (ngx_http_lua_script_add_copy_code(sc, &name, (i == sc->source->len))
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    return ngx_http_lua_script_done(sc);

invalid_variable:

    ngx_log_error(NGX_LOG_ERR, sc->log, 0,
                  "lua script: invalid capturing variable name found in \"%V\"",
                  sc->source);

    return NGX_ERROR;
}