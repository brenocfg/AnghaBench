#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ncaptures; int /*<<< orphan*/  variables_hash_bucket_size; int /*<<< orphan*/  server_names_hash_bucket_size; int /*<<< orphan*/  server_names_hash_max_size; int /*<<< orphan*/  variables_hash_max_size; } ;
typedef  TYPE_1__ ngx_stream_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_align (int /*<<< orphan*/ ,int) ; 
 int ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_conf_init_uint_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
ngx_stream_core_init_main_conf(ngx_conf_t *cf, void *conf)
{
    ngx_stream_core_main_conf_t *cmcf = conf;

    ngx_conf_init_uint_value(cmcf->variables_hash_max_size, 1024);
    ngx_conf_init_uint_value(cmcf->variables_hash_bucket_size, 64);

#if (NGX_STREAM_SNI)
    ngx_conf_init_uint_value(cmcf->server_names_hash_max_size, 512);
    ngx_conf_init_uint_value(cmcf->server_names_hash_bucket_size,
                             ngx_cacheline_size);
#endif

    cmcf->variables_hash_bucket_size =
               ngx_align(cmcf->variables_hash_bucket_size, ngx_cacheline_size);

    if (cmcf->ncaptures) {
        cmcf->ncaptures = (cmcf->ncaptures + 1) * 3;
    }

    return NGX_CONF_OK;
}