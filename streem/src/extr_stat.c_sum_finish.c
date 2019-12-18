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
struct sum_data {scalar_t__ c; scalar_t__ sum; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sum_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_float_value (scalar_t__) ; 

__attribute__((used)) static int
sum_finish(strm_stream* strm, strm_value data)
{
  struct sum_data* d = strm->data;

  strm_emit(strm, strm_float_value(d->sum+d->c), NULL);
  return STRM_OK;
}