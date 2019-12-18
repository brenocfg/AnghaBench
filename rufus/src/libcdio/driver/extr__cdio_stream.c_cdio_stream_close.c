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
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ position; scalar_t__ is_open; int /*<<< orphan*/  user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdio_debug (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
cdio_stream_close(CdioDataSource_t *p_obj)
{
  if (!p_obj) return;

  if (p_obj->is_open) {
    cdio_debug ("closed source...");
    p_obj->op.close(p_obj->user_data);
    p_obj->is_open  = 0;
    p_obj->position = 0;
  }
}