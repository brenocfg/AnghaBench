#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sum_data {int /*<<< orphan*/  func; scalar_t__ num; scalar_t__ c; scalar_t__ sum; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  avg_finish ; 
 int /*<<< orphan*/  iter_sum ; 
 int /*<<< orphan*/  iter_sumf ; 
 struct sum_data* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sum_finish ; 

__attribute__((used)) static int
exec_sum_avg(strm_stream* strm, int argc, strm_value* args, strm_value* ret, int avg)
{
  struct sum_data* d;
  strm_value func;

  strm_get_args(strm, argc, args, "|v", &func);
  d = malloc(sizeof(struct sum_data));
  if (!d) return STRM_NG;
  d->sum = 0;
  d->c = 0;
  d->num = 0;
  if (argc == 0) {
    d->func = strm_nil_value();
    *ret = strm_stream_value(strm_stream_new(strm_filter, iter_sum,
                                             avg ? avg_finish : sum_finish, (void*)d));
  }
  else {
    d->func = func;
    *ret = strm_stream_value(strm_stream_new(strm_filter, iter_sumf,
                                             avg ? avg_finish : sum_finish, (void*)d));
  }
  return STRM_OK;
}