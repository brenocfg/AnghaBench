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
typedef  long ssize_t ;
struct TYPE_5__ {long (* read ) (int /*<<< orphan*/ ,void*,size_t) ;} ;
struct TYPE_6__ {long position; int /*<<< orphan*/  user_data; TYPE_1__ op; } ;
typedef  TYPE_2__ CdioDataSource_t ;

/* Variables and functions */
 int /*<<< orphan*/  _cdio_stream_open_if_necessary (TYPE_2__*) ; 
 long stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t
cdio_stream_read(CdioDataSource_t* p_obj, void *ptr, size_t size, size_t nmemb)
{
  long read_bytes;

  if (!p_obj) return 0;
  if (!_cdio_stream_open_if_necessary(p_obj)) return 0;

  read_bytes = (p_obj->op.read)(p_obj->user_data, ptr, size*nmemb);
  p_obj->position += read_bytes;

  return read_bytes;
}