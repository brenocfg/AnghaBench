#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sa_handle_type_t ;
typedef  int /*<<< orphan*/  sa_handle_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_buf_t ;

/* Variables and functions */
 int dmu_bonus_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int sa_handle_get_from_db (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
sa_handle_get(objset_t *objset, uint64_t objid, void *userp,
    sa_handle_type_t hdl_type, sa_handle_t **handlepp)
{
	dmu_buf_t *db;
	int error;

	if ((error = dmu_bonus_hold(objset, objid, NULL, &db)))
		return (error);

	return (sa_handle_get_from_db(objset, db, userp, hdl_type,
	    handlepp));
}