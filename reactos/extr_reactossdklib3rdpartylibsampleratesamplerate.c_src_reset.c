#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double last_position; double last_ratio; int error; scalar_t__ saved_frames; int /*<<< orphan*/ * saved_data; int /*<<< orphan*/  (* reset ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_STATE ; 
 int SRC_ERR_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int
src_reset (SRC_STATE *state)
{	SRC_PRIVATE *psrc ;

	if ((psrc = (SRC_PRIVATE*) state) == NULL)
		return SRC_ERR_BAD_STATE ;

	if (psrc->reset != NULL)
		psrc->reset (psrc) ;

	psrc->last_position = 0.0 ;
	psrc->last_ratio = 0.0 ;

	psrc->saved_data = NULL ;
	psrc->saved_frames = 0 ;

	psrc->error = SRC_ERR_NO_ERROR ;

	return SRC_ERR_NO_ERROR ;
}