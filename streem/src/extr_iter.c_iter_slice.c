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
struct slice_data {scalar_t__ n; scalar_t__ i; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct slice_data* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  scalar_t__ strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strm_ary_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iter_slice(strm_stream* strm, strm_value data)
{
  struct slice_data* d = strm->data;
  strm_int n = d->n;

  d->buf[d->i++] = data;
  if (d->i == n) {
    strm_array ary = strm_ary_new(d->buf, n);

    d->i = 0;
    strm_emit(strm, strm_ary_value(ary), NULL);
  }
  return STRM_OK;
}