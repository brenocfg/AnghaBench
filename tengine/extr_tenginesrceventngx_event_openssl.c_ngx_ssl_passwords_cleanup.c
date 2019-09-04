#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_4__ {size_t nelts; TYPE_1__* elts; } ;
typedef  TYPE_2__ ngx_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_explicit_memzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_ssl_passwords_cleanup(void *data)
{
    ngx_array_t *passwords = data;

    ngx_str_t   *pwd;
    ngx_uint_t   i;

    pwd = passwords->elts;

    for (i = 0; i < passwords->nelts; i++) {
        ngx_explicit_memzero(pwd[i].data, pwd[i].len);
    }
}