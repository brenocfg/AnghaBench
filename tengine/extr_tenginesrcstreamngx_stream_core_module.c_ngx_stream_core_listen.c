#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_17__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_18__ {int /*<<< orphan*/  sockaddr; } ;
struct TYPE_21__ {int listen; scalar_t__ backlog; int rcvbuf; int sndbuf; scalar_t__ type; int bind; int so_keepalive; int proxy_protocol; TYPE_6__ url; int /*<<< orphan*/  socklen; TYPE_14__ sockaddr; int /*<<< orphan*/  ctx; int /*<<< orphan*/  wildcard; scalar_t__ err; } ;
typedef  TYPE_2__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
typedef  TYPE_2__ ngx_stream_listen_t ;
struct TYPE_22__ {int listen; } ;
typedef  TYPE_4__ ngx_stream_core_srv_conf_t ;
struct TYPE_19__ {int nelts; TYPE_2__* elts; } ;
struct TYPE_23__ {TYPE_17__ listen; } ;
typedef  TYPE_5__ ngx_stream_core_main_conf_t ;
typedef  TYPE_6__ ngx_str_t ;
struct TYPE_25__ {TYPE_1__* args; int /*<<< orphan*/  ctx; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_20__ {size_t nelts; TYPE_6__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_LISTEN_BACKLOG ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 TYPE_2__* ngx_array_push (TYPE_17__*) ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ngx_cmp_sockaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 void* ngx_parse_size (TYPE_6__*) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__* ngx_stream_conf_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_core_module ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static char *
ngx_stream_core_listen(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_stream_core_srv_conf_t  *cscf = conf;

    ngx_str_t                    *value, size;
    ngx_url_t                     u;
    ngx_uint_t                    i, backlog;
    ngx_stream_listen_t          *ls, *als;
    ngx_stream_core_main_conf_t  *cmcf;

    cscf->listen = 1;

    value = cf->args->elts;

    ngx_memzero(&u, sizeof(ngx_url_t));

    u.url = value[1];
    u.listen = 1;

    if (ngx_parse_url(cf->pool, &u) != NGX_OK) {
        if (u.err) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "%s in \"%V\" of the \"listen\" directive",
                               u.err, &u.url);
        }

        return NGX_CONF_ERROR;
    }

    cmcf = ngx_stream_conf_get_module_main_conf(cf, ngx_stream_core_module);

    ls = ngx_array_push(&cmcf->listen);
    if (ls == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(ls, sizeof(ngx_stream_listen_t));

    ngx_memcpy(&ls->sockaddr.sockaddr, &u.sockaddr, u.socklen);

    ls->socklen = u.socklen;
    ls->backlog = NGX_LISTEN_BACKLOG;
    ls->rcvbuf = -1;
    ls->sndbuf = -1;
    ls->type = SOCK_STREAM;
    ls->wildcard = u.wildcard;
    ls->ctx = cf->ctx;

#if (NGX_HAVE_INET6)
    ls->ipv6only = 1;
#endif

    backlog = 0;

    for (i = 2; i < cf->args->nelts; i++) {

#if !(NGX_WIN32)
        if (ngx_strcmp(value[i].data, "udp") == 0) {
            ls->type = SOCK_DGRAM;
            continue;
        }
#endif

#if (NGX_STREAM_SNI)
        if (ngx_strcmp(value[i].data, "default_server") == 0
            || ngx_strcmp(value[i].data, "default") == 0) {

            ls->default_server = 1;
            continue;
        }
#endif

        if (ngx_strcmp(value[i].data, "bind") == 0) {
            ls->bind = 1;
            continue;
        }

        if (ngx_strncmp(value[i].data, "backlog=", 8) == 0) {
            ls->backlog = ngx_atoi(value[i].data + 8, value[i].len - 8);
            ls->bind = 1;

            if (ls->backlog == NGX_ERROR || ls->backlog == 0) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid backlog \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            backlog = 1;

            continue;
        }

        if (ngx_strncmp(value[i].data, "rcvbuf=", 7) == 0) {
            size.len = value[i].len - 7;
            size.data = value[i].data + 7;

            ls->rcvbuf = ngx_parse_size(&size);
            ls->bind = 1;

            if (ls->rcvbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid rcvbuf \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "sndbuf=", 7) == 0) {
            size.len = value[i].len - 7;
            size.data = value[i].data + 7;

            ls->sndbuf = ngx_parse_size(&size);
            ls->bind = 1;

            if (ls->sndbuf == NGX_ERROR) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "invalid sndbuf \"%V\"", &value[i]);
                return NGX_CONF_ERROR;
            }

            continue;
        }

        if (ngx_strncmp(value[i].data, "ipv6only=o", 10) == 0) {
#if (NGX_HAVE_INET6 && defined IPV6_V6ONLY)
            size_t  len;
            u_char  buf[NGX_SOCKADDR_STRLEN];

            if (ls->sockaddr.sockaddr.sa_family == AF_INET6) {

                if (ngx_strcmp(&value[i].data[10], "n") == 0) {
                    ls->ipv6only = 1;

                } else if (ngx_strcmp(&value[i].data[10], "ff") == 0) {
                    ls->ipv6only = 0;

                } else {
                    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                       "invalid ipv6only flags \"%s\"",
                                       &value[i].data[9]);
                    return NGX_CONF_ERROR;
                }

                ls->bind = 1;

            } else {
                len = ngx_sock_ntop(&ls->sockaddr.sockaddr, ls->socklen, buf,
                                    NGX_SOCKADDR_STRLEN, 1);

                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "ipv6only is not supported "
                                   "on addr \"%*s\", ignored", len, buf);
            }

            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "bind ipv6only is not supported "
                               "on this platform");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[i].data, "reuseport") == 0) {
#if (NGX_HAVE_REUSEPORT)
            ls->reuseport = 1;
            ls->bind = 1;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "reuseport is not supported "
                               "on this platform, ignored");
#endif
            continue;
        }

        if (ngx_strcmp(value[i].data, "ssl") == 0) {
#if (NGX_STREAM_SSL)
            ngx_stream_ssl_conf_t  *sslcf;

            sslcf = ngx_stream_conf_get_module_srv_conf(cf,
                                                        ngx_stream_ssl_module);

            sslcf->listen = 1;
            sslcf->file = cf->conf_file->file.name.data;
            sslcf->line = cf->conf_file->line;

            ls->ssl = 1;

            continue;
#else
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "the \"ssl\" parameter requires "
                               "ngx_stream_ssl_module");
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strncmp(value[i].data, "so_keepalive=", 13) == 0) {

            if (ngx_strcmp(&value[i].data[13], "on") == 0) {
                ls->so_keepalive = 1;

            } else if (ngx_strcmp(&value[i].data[13], "off") == 0) {
                ls->so_keepalive = 2;

            } else {

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
                u_char     *p, *end;
                ngx_str_t   s;

                end = value[i].data + value[i].len;
                s.data = value[i].data + 13;

                p = ngx_strlchr(s.data, end, ':');
                if (p == NULL) {
                    p = end;
                }

                if (p > s.data) {
                    s.len = p - s.data;

                    ls->tcp_keepidle = ngx_parse_time(&s, 1);
                    if (ls->tcp_keepidle == (time_t) NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                s.data = (p < end) ? (p + 1) : end;

                p = ngx_strlchr(s.data, end, ':');
                if (p == NULL) {
                    p = end;
                }

                if (p > s.data) {
                    s.len = p - s.data;

                    ls->tcp_keepintvl = ngx_parse_time(&s, 1);
                    if (ls->tcp_keepintvl == (time_t) NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                s.data = (p < end) ? (p + 1) : end;

                if (s.data < end) {
                    s.len = end - s.data;

                    ls->tcp_keepcnt = ngx_atoi(s.data, s.len);
                    if (ls->tcp_keepcnt == NGX_ERROR) {
                        goto invalid_so_keepalive;
                    }
                }

                if (ls->tcp_keepidle == 0 && ls->tcp_keepintvl == 0
                    && ls->tcp_keepcnt == 0)
                {
                    goto invalid_so_keepalive;
                }

                ls->so_keepalive = 1;

#else

                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "the \"so_keepalive\" parameter accepts "
                                   "only \"on\" or \"off\" on this platform");
                return NGX_CONF_ERROR;

#endif
            }

            ls->bind = 1;

            continue;

#if (NGX_HAVE_KEEPALIVE_TUNABLE)
        invalid_so_keepalive:

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "invalid so_keepalive value: \"%s\"",
                               &value[i].data[13]);
            return NGX_CONF_ERROR;
#endif
        }

        if (ngx_strcmp(value[i].data, "proxy_protocol") == 0) {
            ls->proxy_protocol = 1;
            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "the invalid \"%V\" parameter", &value[i]);
        return NGX_CONF_ERROR;
    }

    if (ls->type == SOCK_DGRAM) {
        if (backlog) {
            return "\"backlog\" parameter is incompatible with \"udp\"";
        }

#if (NGX_STREAM_SSL)
        if (ls->ssl) {
            return "\"ssl\" parameter is incompatible with \"udp\"";
        }
#endif

        if (ls->so_keepalive) {
            return "\"so_keepalive\" parameter is incompatible with \"udp\"";
        }

        if (ls->proxy_protocol) {
            return "\"proxy_protocol\" parameter is incompatible with \"udp\"";
        }
    }
#if (NGX_STREAM_SNI)
    return NGX_CONF_OK;
#endif

    als = cmcf->listen.elts;

    for (i = 0; i < cmcf->listen.nelts - 1; i++) {
        if (ls->type != als[i].type) {
            continue;
        }

        if (ngx_cmp_sockaddr(&als[i].sockaddr.sockaddr, als[i].socklen,
                             &ls->sockaddr.sockaddr, ls->socklen, 1)
            != NGX_OK)
        {
            continue;
        }

        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "duplicate \"%V\" address and port pair", &u.url);
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}