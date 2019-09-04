#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* install_file; scalar_t__ callback; scalar_t__ uri; } ;
typedef  TYPE_1__ install_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBindStatusCallback_Release (scalar_t__) ; 
 int /*<<< orphan*/  IUri_Release (scalar_t__) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static void release_install_ctx(install_ctx_t *ctx)
{
    if(ctx->uri)
        IUri_Release(ctx->uri);
    if(ctx->callback)
        IBindStatusCallback_Release(ctx->callback);
    heap_free(ctx->install_file);
    heap_free(ctx);
}