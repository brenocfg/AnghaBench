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
struct TYPE_3__ {int /*<<< orphan*/  gen; } ;
typedef  TYPE_1__ ngx_http_tfs_json_gen_t ;

/* Variables and functions */
 int /*<<< orphan*/  yajl_gen_free (int /*<<< orphan*/ ) ; 

void
ngx_http_tfs_json_destroy(ngx_http_tfs_json_gen_t *tj_gen)
{
    if (tj_gen != NULL) {
        yajl_gen_free(tj_gen->gen);
    }
}