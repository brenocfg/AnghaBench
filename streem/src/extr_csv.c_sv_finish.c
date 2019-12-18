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
struct csv_data {struct csv_data* types; scalar_t__ headers; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct csv_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct csv_data*) ; 
 scalar_t__ strm_ary_null ; 
 int /*<<< orphan*/  strm_ary_value (scalar_t__) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sv_finish(strm_stream* strm, strm_value data)
{
  struct csv_data *cd = strm->data;

  if (cd->headers && cd->types == NULL) {
    strm_emit(strm, strm_ary_value(cd->headers), NULL);
    cd->headers = strm_ary_null;
  }
  /* memory deallocation */
  if (cd->types) {
    free(cd->types);
    cd->types = NULL;
  }
  free(cd);
  return STRM_OK;
}