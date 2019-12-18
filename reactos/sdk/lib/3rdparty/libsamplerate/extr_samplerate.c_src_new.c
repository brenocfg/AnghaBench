#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int channels; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  SRC_STATE ;
typedef  TYPE_1__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_CHANNEL_COUNT ; 
 int SRC_ERR_BAD_CONVERTER ; 
 int SRC_ERR_MALLOC_FAILED ; 
 int SRC_ERR_NO_ERROR ; 
 int /*<<< orphan*/  SRC_MODE_PROCESS ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int psrc_set_converter (TYPE_1__*,int) ; 
 int /*<<< orphan*/  src_reset (int /*<<< orphan*/ *) ; 

SRC_STATE *
src_new (int converter_type, int channels, int *error)
{	SRC_PRIVATE	*psrc ;

	if (error)
		*error = SRC_ERR_NO_ERROR ;

	if (channels < 1)
	{	if (error)
			*error = SRC_ERR_BAD_CHANNEL_COUNT ;
		return NULL ;
		} ;

	if ((psrc = calloc (1, sizeof (*psrc))) == NULL)
	{	if (error)
			*error = SRC_ERR_MALLOC_FAILED ;
		return NULL ;
		} ;

	psrc->channels = channels ;
	psrc->mode = SRC_MODE_PROCESS ;

	if (psrc_set_converter (psrc, converter_type) != SRC_ERR_NO_ERROR)
	{	if (error)
			*error = SRC_ERR_BAD_CONVERTER ;
		free (psrc) ;
		psrc = NULL ;
		} ;

	src_reset ((SRC_STATE*) psrc) ;

	return (SRC_STATE*) psrc ;
}