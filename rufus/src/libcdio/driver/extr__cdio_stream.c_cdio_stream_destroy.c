#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/ * user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_stream_close (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
cdio_stream_destroy(CdioDataSource_t *p_obj)
{
  if (!p_obj) return;

  cdio_stream_close(p_obj);

  p_obj->op.free(p_obj->user_data);
  p_obj->user_data = NULL;
  free(p_obj);
}