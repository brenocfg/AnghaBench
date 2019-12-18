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
struct rbk_data {int /*<<< orphan*/  tbl; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct rbk_data* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int STRM_OK ; 
 scalar_t__ kh_begin (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_exist (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kh_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rbk_finish(strm_stream* strm, strm_value data)
{
  struct rbk_data *d = strm->data;
  khiter_t i;

  for (i=kh_begin(d->tbl); i!=kh_end(d->tbl); i++) {
    if (kh_exist(d->tbl, i)) {
      strm_value values[2];

      values[0] = kh_key(d->tbl, i);
      values[1] = kh_value(d->tbl, i);
      strm_emit(strm, strm_ary_new(values, 2), NULL);
    }
  }
  return STRM_OK;
}