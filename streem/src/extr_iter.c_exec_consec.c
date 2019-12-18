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
struct slice_data {int n; void* buf; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  finish_consec ; 
 int /*<<< orphan*/  free (struct slice_data*) ; 
 int /*<<< orphan*/  iter_consec ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_consec(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct slice_data* d;
  strm_int n;

  strm_get_args(strm, argc, args, "i", &n);
  d = malloc(sizeof(*d));
  if (!d) return STRM_NG;
  d->n = n;
  d->i = 0;
  d->buf = malloc(n*sizeof(strm_value));
  if (!d->buf) {
    free(d);
    return STRM_NG;
  }
  *ret = strm_stream_value(strm_stream_new(strm_filter, iter_consec, finish_consec, (void*)d));
  return STRM_OK;
}