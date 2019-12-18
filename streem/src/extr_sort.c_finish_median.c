#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sort_data {struct sort_data* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sort_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct sort_data*) ; 
 int /*<<< orphan*/  quick_median (struct sort_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
finish_median(strm_stream* strm, strm_value data)
{
  struct sort_data* d = strm->data;
  strm_value v;

  v = quick_median(d->buf, d->len);
  free(d->buf);
  strm_emit(strm, v, NULL);
  free(d);
  return STRM_OK;
}