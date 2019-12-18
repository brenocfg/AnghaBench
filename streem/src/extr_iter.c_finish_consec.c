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
struct slice_data {struct slice_data* buf; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {struct slice_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct slice_data*) ; 

__attribute__((used)) static int
finish_consec(strm_stream* strm, strm_value data)
{
  struct slice_data* d = strm->data;

  free(d->buf);
  free(d);
  return STRM_OK;
}