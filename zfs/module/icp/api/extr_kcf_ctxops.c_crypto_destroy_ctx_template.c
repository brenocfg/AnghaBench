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
struct TYPE_4__ {int ct_size; struct TYPE_4__* ct_prov_tmpl; } ;
typedef  TYPE_1__ kcf_ctx_template_t ;
typedef  scalar_t__ crypto_ctx_template_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 

void
crypto_destroy_ctx_template(crypto_ctx_template_t tmpl)
{
	kcf_ctx_template_t *ctx_tmpl = (kcf_ctx_template_t *)tmpl;

	if (ctx_tmpl == NULL)
		return;

	ASSERT(ctx_tmpl->ct_prov_tmpl != NULL);

	bzero(ctx_tmpl->ct_prov_tmpl, ctx_tmpl->ct_size);
	kmem_free(ctx_tmpl->ct_prov_tmpl, ctx_tmpl->ct_size);
	kmem_free(ctx_tmpl, sizeof (kcf_ctx_template_t));
}