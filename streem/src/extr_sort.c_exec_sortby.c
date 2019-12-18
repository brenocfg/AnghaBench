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
struct sortby_value {int dummy; } ;
struct sortby_data {int capa; void* buf; scalar_t__ len; int /*<<< orphan*/  func; int /*<<< orphan*/ * strm; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int SORT_FIRST_CAPA ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  finish_sortby ; 
 int /*<<< orphan*/  free (struct sortby_data*) ; 
 int /*<<< orphan*/  iter_sortby ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_sortby(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct sortby_data* d;
  strm_value func;

  strm_get_args(strm, argc, args, "v", &func);

  d = malloc(sizeof(struct sortby_data));
  if (!d) return STRM_NG;
  d->strm = strm;
  d->func = func;
  d->len = 0;
  d->capa = SORT_FIRST_CAPA;
  d->buf = malloc(sizeof(struct sortby_value)*SORT_FIRST_CAPA);
  if (!d->buf) {
    free(d);
    return STRM_NG;
  }
  *ret = strm_stream_value(strm_stream_new(strm_filter, iter_sortby,
                                           finish_sortby, (void*)d));
  return STRM_OK;
}