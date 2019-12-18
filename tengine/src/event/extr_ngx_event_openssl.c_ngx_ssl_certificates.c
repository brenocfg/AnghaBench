#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_ssl_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_6__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
typedef  TYPE_1__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_ssl_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

ngx_int_t
ngx_ssl_certificates(ngx_conf_t *cf, ngx_ssl_t *ssl, ngx_array_t *certs,
    ngx_array_t *keys, ngx_array_t *passwords)
{
    ngx_str_t   *cert, *key;
    ngx_uint_t   i;

    cert = certs->elts;
    key = keys->elts;

    for (i = 0; i < certs->nelts; i++) {

        if (ngx_ssl_certificate(cf, ssl, &cert[i], &key[i], passwords)
            != NGX_OK)
        {
            return NGX_ERROR;
        }
    }

    return NGX_OK;
}