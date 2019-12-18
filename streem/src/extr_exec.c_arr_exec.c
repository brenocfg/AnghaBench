#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct array_data {scalar_t__ n; int /*<<< orphan*/  arr; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_6__ {struct array_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 scalar_t__ strm_ary_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int (*) (TYPE_1__*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  strm_stream_close (TYPE_1__*) ; 

__attribute__((used)) static int
arr_exec(strm_stream* strm, strm_value data)
{
  struct array_data *arrd = strm->data;

  if (arrd->n == strm_ary_len(arrd->arr)) {
    strm_stream_close(strm);
    return STRM_OK;
  }
  strm_emit(strm, strm_ary_ptr(arrd->arr)[arrd->n++], arr_exec);
  return STRM_OK;
}