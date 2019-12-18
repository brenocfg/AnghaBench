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
struct take_data {scalar_t__ n; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct take_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 

__attribute__((used)) static int
iter_take(strm_stream* strm, strm_value data)
{
  struct take_data* d = strm->data;

  strm_emit(strm, data, NULL);
  d->n--;
  if (d->n == 0) {
    strm_stream_close(strm);
  }
  return STRM_OK;
}