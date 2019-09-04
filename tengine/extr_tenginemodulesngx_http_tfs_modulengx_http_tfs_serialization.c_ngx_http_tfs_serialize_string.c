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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_serialize_string(u_char **p,
    ngx_str_t *string)
{
    if (p == NULL || *p == NULL || string == NULL) {
        return NGX_ERROR;
    }

    if (string->len == 0) {
        *((uint32_t *)*p) = 0;

    } else {
        *((uint32_t *)*p) = string->len + 1;
    }
    *p += sizeof(uint32_t);

    if (string->len > 0) {
        ngx_memcpy(*p, string->data, string->len);
        *p += string->len + 1;
    }

    return NGX_OK;
}