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
typedef  int /*<<< orphan*/ * src_callback_t ;
struct TYPE_2__ {void* user_callback_data; int /*<<< orphan*/ * callback_func; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_CALLBACK ; 
 int /*<<< orphan*/  SRC_MODE_CALLBACK ; 
 int /*<<< orphan*/ * src_new (int,int,int*) ; 
 int /*<<< orphan*/  src_reset (int /*<<< orphan*/ *) ; 

SRC_STATE*
src_callback_new (src_callback_t func, int converter_type, int channels, int *error, void* cb_data)
{	SRC_STATE	*src_state ;

	if (func == NULL)
	{	if (error)
			*error = SRC_ERR_BAD_CALLBACK ;
		return NULL ;
		} ;

	if (error != NULL)
		*error = 0 ;

	if ((src_state = src_new (converter_type, channels, error)) == NULL)
		return NULL ;

	src_reset (src_state) ;

	((SRC_PRIVATE*) src_state)->mode = SRC_MODE_CALLBACK ;
	((SRC_PRIVATE*) src_state)->callback_func = func ;
	((SRC_PRIVATE*) src_state)->user_callback_data = cb_data ;

	return src_state ;
}