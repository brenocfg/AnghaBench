#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int nelts; TYPE_3__* elts; } ;
struct TYPE_11__ {TYPE_1__ passwd; TYPE_2__ args; } ;
typedef  TYPE_4__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_mail_pop3_pass(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t  *arg;

    if (s->args.nelts != 1) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    arg = s->args.elts;
    s->passwd.len = arg[0].len;
    s->passwd.data = ngx_pnalloc(c->pool, s->passwd.len);
    if (s->passwd.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->passwd.data, arg[0].data, s->passwd.len);

#if (NGX_DEBUG_MAIL_PASSWD)
    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "pop3 passwd: \"%V\"", &s->passwd);
#endif

    return NGX_DONE;
}