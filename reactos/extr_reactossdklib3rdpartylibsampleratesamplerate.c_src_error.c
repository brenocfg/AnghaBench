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
struct TYPE_2__ {int error; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_NO_ERROR ; 

int
src_error (SRC_STATE *state)
{	if (state)
		return ((SRC_PRIVATE*) state)->error ;
	return SRC_ERR_NO_ERROR ;
}