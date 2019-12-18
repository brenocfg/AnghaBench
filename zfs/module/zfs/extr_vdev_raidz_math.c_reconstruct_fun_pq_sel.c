#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  raidz_rec_f ;
struct TYPE_5__ {TYPE_1__* rm_ops; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_4__ {int /*<<< orphan*/ * rec; } ;

/* Variables and functions */
 size_t CODE_P ; 
 size_t CODE_Q ; 
 size_t RAIDZ_REC_P ; 
 size_t RAIDZ_REC_PQ ; 
 size_t RAIDZ_REC_Q ; 

__attribute__((used)) static raidz_rec_f
reconstruct_fun_pq_sel(raidz_map_t *rm, const int *parity_valid,
    const int nbaddata)
{
	if (nbaddata == 1) {
		if (parity_valid[CODE_P]) {
			return (rm->rm_ops->rec[RAIDZ_REC_P]);
		} else if (parity_valid[CODE_Q]) {
			return (rm->rm_ops->rec[RAIDZ_REC_Q]);
		}
	} else if (nbaddata == 2 &&
	    parity_valid[CODE_P] && parity_valid[CODE_Q]) {
		return (rm->rm_ops->rec[RAIDZ_REC_PQ]);
	}
	return ((raidz_rec_f) NULL);
}