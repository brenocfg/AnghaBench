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
struct uniq_data {void* last; scalar_t__ init; } ;
typedef  void* strm_value ;
struct TYPE_4__ {struct uniq_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_value_eq (void*,void*) ; 

__attribute__((used)) static int
iter_uniq(strm_stream* strm, strm_value data)
{
  struct uniq_data* d = strm->data;

  if (!d->init) {
    d->init = TRUE;
    d->last = data;
    strm_emit(strm, data, NULL);
    return STRM_OK;
  }
  if (!strm_value_eq(data, d->last)) {
    d->last = data;
    strm_emit(strm, data, NULL);
  }
  return STRM_OK;
}