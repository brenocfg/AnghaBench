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
struct reduce_data {int init; void* acc; int /*<<< orphan*/  func; } ;
typedef  void* strm_value ;
struct TYPE_4__ {struct reduce_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ strm_funcall (TYPE_1__*,int /*<<< orphan*/ ,int,void**,void**) ; 

__attribute__((used)) static int
iter_reduce(strm_stream* strm, strm_value data)
{
  struct reduce_data* d = strm->data;
  strm_value args[2];

  /* first acc */
  if (!d->init) {
    d->init = 1;
    d->acc = data;
    return STRM_OK;
  }

  args[0] = d->acc;
  args[1] = data;
  if (strm_funcall(strm, d->func, 2, args, &data) == STRM_NG) {
    return STRM_NG;
  }
  d->acc = data;
  return STRM_OK;
}