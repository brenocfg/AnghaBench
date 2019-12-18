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
struct TYPE_4__ {int /*<<< orphan*/  zcd_node; int /*<<< orphan*/  zcd_spa; int /*<<< orphan*/  zcd_txg; } ;
typedef  TYPE_1__ ztest_cb_data_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_link_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* umem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ztest_cb_data_t *
ztest_create_cb_data(objset_t *os, uint64_t txg)
{
	ztest_cb_data_t *cb_data;

	cb_data = umem_zalloc(sizeof (ztest_cb_data_t), UMEM_NOFAIL);

	cb_data->zcd_txg = txg;
	cb_data->zcd_spa = dmu_objset_spa(os);
	list_link_init(&cb_data->zcd_node);

	return (cb_data);
}