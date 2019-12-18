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
struct uniq_data {int /*<<< orphan*/  init; void* func; void* last; } ;
typedef  void* strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  iter_uniq ; 
 int /*<<< orphan*/  iter_uniqf ; 
 struct uniq_data* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,void**,char*,void**) ; 
 scalar_t__ strm_nil_p (void*) ; 
 void* strm_nil_value () ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 void* strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_uniq(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct uniq_data* d;
  strm_value func = strm_nil_value();

  strm_get_args(strm, argc, args, "|v", &func);
  d = malloc(sizeof(*d));
  if (!d) return STRM_NG;
  d->last = strm_nil_value();
  d->func = func;
  d->init = FALSE;
  *ret = strm_stream_value(strm_stream_new(strm_filter,
                                           strm_nil_p(func) ? iter_uniq : iter_uniqf,
                                           NULL, (void*)d));
  return STRM_OK;
}