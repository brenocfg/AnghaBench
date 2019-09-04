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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_3__ {int /*<<< orphan*/  position; int /*<<< orphan*/  is_open; } ;
typedef  TYPE_1__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_OP_UNINIT ; 

off_t
cdio_stream_getpos(CdioDataSource_t* p_obj, /*out*/ off_t *i_offset)
{
  if (!p_obj || !p_obj->is_open) return DRIVER_OP_UNINIT;
  return *i_offset = p_obj->position;
}