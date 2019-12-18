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
struct TYPE_4__ {struct TYPE_4__* private_data; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

SRC_STATE *
src_delete (SRC_STATE *state)
{	SRC_PRIVATE *psrc ;

	psrc = (SRC_PRIVATE*) state ;
	if (psrc)
	{	if (psrc->private_data)
			free (psrc->private_data) ;
		memset (psrc, 0, sizeof (SRC_PRIVATE)) ;
		free (psrc) ;
		} ;

	return NULL ;
}