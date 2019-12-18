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
struct TYPE_4__ {int end_of_input; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  src_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * src_new (int,int,int*) ; 
 int src_process (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
src_simple (SRC_DATA *src_data, int converter, int channels)
{	SRC_STATE	*src_state ;
	int 		error ;

	if ((src_state = src_new (converter, channels, &error)) == NULL)
		return error ;

	src_data->end_of_input = 1 ; /* Only one buffer worth of input. */

	error = src_process (src_state, src_data) ;

	src_delete (src_state) ;

	return error ;
}