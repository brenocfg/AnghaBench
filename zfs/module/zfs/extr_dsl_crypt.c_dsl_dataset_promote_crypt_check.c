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
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ dd_crypto_obj; scalar_t__ dd_object; struct TYPE_6__* dd_parent; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int dsl_dir_get_encryption_root_ddobj (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ dsl_dir_is_clone (TYPE_1__*) ; 

int
dsl_dataset_promote_crypt_check(dsl_dir_t *target, dsl_dir_t *origin)
{
	int ret;
	uint64_t rddobj, op_rddobj, tp_rddobj;

	/* If the dataset is not encrypted we don't need to check anything */
	if (origin->dd_crypto_obj == 0)
		return (0);

	/*
	 * If we are not changing the first origin snapshot in a chain
	 * the encryption root won't change either.
	 */
	if (dsl_dir_is_clone(origin))
		return (0);

	/*
	 * If the origin is the encryption root we will update
	 * the DSL Crypto Key to point to the target instead.
	 */
	ret = dsl_dir_get_encryption_root_ddobj(origin, &rddobj);
	if (ret != 0)
		return (ret);

	if (rddobj == origin->dd_object)
		return (0);

	/*
	 * The origin is inheriting its encryption root from its parent.
	 * Check that the parent of the target has the same encryption root.
	 */
	ret = dsl_dir_get_encryption_root_ddobj(origin->dd_parent, &op_rddobj);
	if (ret == ENOENT)
		return (SET_ERROR(EACCES));
	else if (ret != 0)
		return (ret);

	ret = dsl_dir_get_encryption_root_ddobj(target->dd_parent, &tp_rddobj);
	if (ret == ENOENT)
		return (SET_ERROR(EACCES));
	else if (ret != 0)
		return (ret);

	if (op_rddobj != tp_rddobj)
		return (SET_ERROR(EACCES));

	return (0);
}