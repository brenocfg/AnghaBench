#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* nvs_ops; } ;
typedef  TYPE_2__ nvstream_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_6__ {int (* nvs_nvpair ) (TYPE_2__*,int /*<<< orphan*/ *,size_t*) ;int (* nvs_nvp_op ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 size_t NVP_SIZE_CALC (int,int /*<<< orphan*/ ) ; 
 scalar_t__ i_validate_nvpair (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvp_buf_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nvp_buf_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvp_buf_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_free (int /*<<< orphan*/ *) ; 
 int nvt_add_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,size_t*) ; 
 int stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nvs_decode_pairs(nvstream_t *nvs, nvlist_t *nvl)
{
	nvpair_t *nvp;
	size_t nvsize;
	int err;

	/*
	 * Get decoded size of next pair in stream, alloc
	 * memory for nvpair_t, then decode the nvpair
	 */
	while ((err = nvs->nvs_ops->nvs_nvpair(nvs, NULL, &nvsize)) == 0) {
		if (nvsize == 0) /* end of list */
			break;

		/* make sure len makes sense */
		if (nvsize < NVP_SIZE_CALC(1, 0))
			return (EFAULT);

		if ((nvp = nvp_buf_alloc(nvl, nvsize)) == NULL)
			return (ENOMEM);

		if ((err = nvs->nvs_ops->nvs_nvp_op(nvs, nvp)) != 0) {
			nvp_buf_free(nvl, nvp);
			return (err);
		}

		if (i_validate_nvpair(nvp) != 0) {
			nvpair_free(nvp);
			nvp_buf_free(nvl, nvp);
			return (EFAULT);
		}

		err = nvt_add_nvpair(nvl, nvp);
		if (err != 0) {
			nvpair_free(nvp);
			nvp_buf_free(nvl, nvp);
			return (err);
		}
		nvp_buf_link(nvl, nvp);
	}
	return (err);
}