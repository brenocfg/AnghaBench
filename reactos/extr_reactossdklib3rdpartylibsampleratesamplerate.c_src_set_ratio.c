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
struct TYPE_2__ {double last_ratio; int /*<<< orphan*/ * const_process; int /*<<< orphan*/ * vari_process; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_PROC_PTR ; 
 int SRC_ERR_BAD_SRC_RATIO ; 
 int SRC_ERR_BAD_STATE ; 
 int SRC_ERR_NO_ERROR ; 
 scalar_t__ is_bad_src_ratio (double) ; 

int
src_set_ratio (SRC_STATE *state, double new_ratio)
{	SRC_PRIVATE *psrc ;

	psrc = (SRC_PRIVATE*) state ;

	if (psrc == NULL)
		return SRC_ERR_BAD_STATE ;
	if (psrc->vari_process == NULL || psrc->const_process == NULL)
		return SRC_ERR_BAD_PROC_PTR ;

	if (is_bad_src_ratio (new_ratio))
		return SRC_ERR_BAD_SRC_RATIO ;

	psrc->last_ratio = new_ratio ;

	return SRC_ERR_NO_ERROR ;
}