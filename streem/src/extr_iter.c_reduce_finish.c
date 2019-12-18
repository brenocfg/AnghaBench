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
struct reduce_data {int /*<<< orphan*/  acc; int /*<<< orphan*/  init; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct reduce_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
reduce_finish(strm_stream* strm, strm_value data)
{
  struct reduce_data* d = strm->data;

  if (!d->init) return STRM_NG;
  strm_emit(strm, d->acc, NULL);
  return STRM_OK;
}