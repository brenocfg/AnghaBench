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
typedef  int off_t ;
struct TYPE_5__ {int (* stat ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_stream_open_if_necessary (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

off_t
cdio_stream_stat(CdioDataSource_t *p_obj)
{
  if (!p_obj) return -1;
  if (!_cdio_stream_open_if_necessary(p_obj)) return -1;

  return p_obj->op.stat(p_obj->user_data);
}