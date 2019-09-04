#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_8__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ name; } ;
typedef  TYPE_3__ ngx_check_conf_t ;

/* Variables and functions */
 TYPE_3__* ngx_check_types ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_check_conf_t *
ngx_http_get_check_type_conf(ngx_str_t *str)
{
    ngx_uint_t  i;

    for (i = 0; /* void */ ; i++) {

        if (ngx_check_types[i].type == 0) {
            break;
        }

        if (str->len != ngx_check_types[i].name.len) {
            continue;
        }

        if (ngx_strncmp(str->data, ngx_check_types[i].name.data,
                        str->len) == 0)
        {
            return &ngx_check_types[i];
        }
    }

    return NULL;
}