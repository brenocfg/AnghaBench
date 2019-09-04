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
struct TYPE_3__ {int /*<<< orphan*/  out; int /*<<< orphan*/  smtp_to; int /*<<< orphan*/  smtp_from; } ;
typedef  TYPE_1__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_str_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtp_ok ; 

__attribute__((used)) static ngx_int_t
ngx_mail_smtp_rset(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_null(&s->smtp_from);
    ngx_str_null(&s->smtp_to);
    ngx_str_set(&s->out, smtp_ok);

    return NGX_OK;
}