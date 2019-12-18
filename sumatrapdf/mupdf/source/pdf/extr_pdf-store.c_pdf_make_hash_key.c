#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pdf_obj ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  i; } ;
struct TYPE_6__ {TYPE_1__ pi; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_store_hash ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  pdf_get_indirect_document (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_is_indirect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdf_to_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pdf_make_hash_key(fz_context *ctx, fz_store_hash *hash, void *key_)
{
	pdf_obj *key = (pdf_obj *)key_;

	if (!pdf_is_indirect(ctx, key))
		return 0;
	hash->u.pi.i = pdf_to_num(ctx, key);
	hash->u.pi.ptr = pdf_get_indirect_document(ctx, key);
	return 1;
}