#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_16__ {size_t sa_num_attrs; } ;
typedef  TYPE_2__ sa_os_t ;
struct TYPE_17__ {int /*<<< orphan*/  sa_spill; TYPE_11__* sa_spill_tab; int /*<<< orphan*/  sa_bonus; TYPE_11__* sa_bonus_tab; TYPE_1__* sa_os; } ;
typedef  TYPE_3__ sa_handle_t ;
typedef  int sa_data_op_t ;
struct TYPE_18__ {size_t sa_attr; scalar_t__ sa_size; scalar_t__ sa_length; int /*<<< orphan*/ * sa_data; int /*<<< orphan*/  sa_data_func; int /*<<< orphan*/ * sa_addr; } ;
typedef  TYPE_4__ sa_bulk_attr_t ;
typedef  int sa_buf_type_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {TYPE_2__* os_sa; } ;
struct TYPE_14__ {int /*<<< orphan*/ * sa_idx_tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ECKSUM ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  SA_ADD ; 
 int /*<<< orphan*/  SA_ATTR_INFO (TYPE_2__*,TYPE_11__*,int /*<<< orphan*/ ,size_t,TYPE_4__,int,TYPE_3__*) ; 
 int SA_BONUS ; 
 int /*<<< orphan*/  SA_COPY_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SA_GET_HDR (TYPE_3__*,int) ; 
#define  SA_LOOKUP 129 
 int /*<<< orphan*/  SA_REPLACE ; 
 int SA_SPILL ; 
#define  SA_UPDATE 128 
 int SET_ERROR (int) ; 
 scalar_t__ TOC_ATTR_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sa_get_spill (TYPE_3__*) ; 
 int sa_modify_attrs (TYPE_3__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

int
sa_attr_op(sa_handle_t *hdl, sa_bulk_attr_t *bulk, int count,
    sa_data_op_t data_op, dmu_tx_t *tx)
{
	sa_os_t *sa = hdl->sa_os->os_sa;
	int i;
	int error = 0;
	sa_buf_type_t buftypes;

	buftypes = 0;

	ASSERT(count > 0);
	for (i = 0; i != count; i++) {
		ASSERT(bulk[i].sa_attr <= hdl->sa_os->os_sa->sa_num_attrs);

		bulk[i].sa_addr = NULL;
		/* First check the bonus buffer */

		if (hdl->sa_bonus_tab && TOC_ATTR_PRESENT(
		    hdl->sa_bonus_tab->sa_idx_tab[bulk[i].sa_attr])) {
			SA_ATTR_INFO(sa, hdl->sa_bonus_tab,
			    SA_GET_HDR(hdl, SA_BONUS),
			    bulk[i].sa_attr, bulk[i], SA_BONUS, hdl);
			if (tx && !(buftypes & SA_BONUS)) {
				dmu_buf_will_dirty(hdl->sa_bonus, tx);
				buftypes |= SA_BONUS;
			}
		}
		if (bulk[i].sa_addr == NULL &&
		    ((error = sa_get_spill(hdl)) == 0)) {
			if (TOC_ATTR_PRESENT(
			    hdl->sa_spill_tab->sa_idx_tab[bulk[i].sa_attr])) {
				SA_ATTR_INFO(sa, hdl->sa_spill_tab,
				    SA_GET_HDR(hdl, SA_SPILL),
				    bulk[i].sa_attr, bulk[i], SA_SPILL, hdl);
				if (tx && !(buftypes & SA_SPILL) &&
				    bulk[i].sa_size == bulk[i].sa_length) {
					dmu_buf_will_dirty(hdl->sa_spill, tx);
					buftypes |= SA_SPILL;
				}
			}
		}
		if (error && error != ENOENT) {
			return ((error == ECKSUM) ? EIO : error);
		}

		switch (data_op) {
		case SA_LOOKUP:
			if (bulk[i].sa_addr == NULL)
				return (SET_ERROR(ENOENT));
			if (bulk[i].sa_data) {
				SA_COPY_DATA(bulk[i].sa_data_func,
				    bulk[i].sa_addr, bulk[i].sa_data,
				    bulk[i].sa_size);
			}
			continue;

		case SA_UPDATE:
			/* existing rewrite of attr */
			if (bulk[i].sa_addr &&
			    bulk[i].sa_size == bulk[i].sa_length) {
				SA_COPY_DATA(bulk[i].sa_data_func,
				    bulk[i].sa_data, bulk[i].sa_addr,
				    bulk[i].sa_length);
				continue;
			} else if (bulk[i].sa_addr) { /* attr size change */
				error = sa_modify_attrs(hdl, bulk[i].sa_attr,
				    SA_REPLACE, bulk[i].sa_data_func,
				    bulk[i].sa_data, bulk[i].sa_length, tx);
			} else { /* adding new attribute */
				error = sa_modify_attrs(hdl, bulk[i].sa_attr,
				    SA_ADD, bulk[i].sa_data_func,
				    bulk[i].sa_data, bulk[i].sa_length, tx);
			}
			if (error)
				return (error);
			break;
		default:
			break;
		}
	}
	return (error);
}