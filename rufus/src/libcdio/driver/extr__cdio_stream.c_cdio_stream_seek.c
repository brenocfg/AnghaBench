#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int (* seek ) (int /*<<< orphan*/ ,scalar_t__,int) ;} ;
struct TYPE_6__ {scalar_t__ position; int /*<<< orphan*/  user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int DRIVER_OP_ERROR ; 
 int DRIVER_OP_UNINIT ; 
 int /*<<< orphan*/  _cdio_stream_open_if_necessary (TYPE_2__*) ; 
 int /*<<< orphan*/  cdio_warn (char*,scalar_t__,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int) ; 

int
cdio_stream_seek(CdioDataSource_t* p_obj, off_t offset, int whence)
{
  if (!p_obj) return DRIVER_OP_UNINIT;

  if (!_cdio_stream_open_if_necessary(p_obj))
    /* errno is set by _cdio_stream_open_if necessary. */
    return DRIVER_OP_ERROR;

  if (offset < 0) return DRIVER_OP_ERROR;
  if (p_obj->position < 0) return DRIVER_OP_ERROR;

  if (p_obj->position != offset) {
#ifdef STREAM_DEBUG
    cdio_warn("had to reposition DataSource from %ld to %ld!", p_obj->position, offset);
#endif
    p_obj->position = offset;
    return p_obj->op.seek(p_obj->user_data, offset, whence);
  }

  return 0;
}