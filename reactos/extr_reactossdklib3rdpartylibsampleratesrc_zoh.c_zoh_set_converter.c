#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int channels; int /*<<< orphan*/  zoh_magic_marker; } ;
typedef  TYPE_1__ ZOH_DATA ;
struct TYPE_8__ {int channels; int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;void* vari_process; void* const_process; TYPE_1__* private_data; } ;
typedef  TYPE_2__ SRC_PRIVATE ;

/* Variables and functions */
 int SRC_ERR_BAD_CONVERTER ; 
 int SRC_ERR_MALLOC_FAILED ; 
 int SRC_ERR_NO_ERROR ; 
 int SRC_ZERO_ORDER_HOLD ; 
 int /*<<< orphan*/  ZOH_MAGIC_MARKER ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  zoh_reset (TYPE_2__*) ; 
 void* zoh_vari_process ; 

int
zoh_set_converter (SRC_PRIVATE *psrc, int src_enum)
{	ZOH_DATA *priv = NULL ;

	if (src_enum != SRC_ZERO_ORDER_HOLD)
		return SRC_ERR_BAD_CONVERTER ;

	if (psrc->private_data != NULL)
	{	free (psrc->private_data) ;
		psrc->private_data = NULL ;
		} ;

	if (psrc->private_data == NULL)
	{	priv = calloc (1, sizeof (*priv) + psrc->channels * sizeof (float)) ;
		psrc->private_data = priv ;
		} ;

	if (priv == NULL)
		return SRC_ERR_MALLOC_FAILED ;

	priv->zoh_magic_marker = ZOH_MAGIC_MARKER ;
	priv->channels = psrc->channels ;

	psrc->const_process = zoh_vari_process ;
	psrc->vari_process = zoh_vari_process ;
	psrc->reset = zoh_reset ;

	zoh_reset (psrc) ;

	return SRC_ERR_NO_ERROR ;
}