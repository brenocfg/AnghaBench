#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct strm_lambda {int dummy; } ;
struct array_data {scalar_t__ n; int /*<<< orphan*/  arr; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_7__ {scalar_t__ mode; } ;
typedef  TYPE_1__ strm_stream ;
typedef  void* strm_cfunc ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_IO_READ ; 
 int /*<<< orphan*/  STRM_IO_WRITE ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  arr_exec ; 
 int /*<<< orphan*/  blk_exec ; 
 int /*<<< orphan*/ * cfunc_closer ; 
 int /*<<< orphan*/  cfunc_exec ; 
 struct array_data* malloc (int) ; 
 scalar_t__ strm_array_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_cfunc_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_consumer ; 
 scalar_t__ strm_filter ; 
 scalar_t__ strm_io_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_io_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strm_lambda_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_producer ; 
 int /*<<< orphan*/  strm_raise (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strm_stream_connect (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  strm_stream_new (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ strm_stream_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_ary (int /*<<< orphan*/ ) ; 
 void* strm_value_cfunc (int /*<<< orphan*/ ) ; 
 struct strm_lambda* strm_value_lambda (int /*<<< orphan*/ ) ; 
 TYPE_1__* strm_value_stream (int /*<<< orphan*/ ) ; 

int
strm_connect(strm_stream* strm, strm_value src, strm_value dst, strm_value* ret)
{
  /* src: io */
  if (strm_io_p(src)) {
    src = strm_stream_value(strm_io_stream(src, STRM_IO_READ));
  }
  /* src: lambda */
  else if (strm_lambda_p(src)) {
    struct strm_lambda* lmbd = strm_value_lambda(src);
    src = strm_stream_value(strm_stream_new(strm_filter, blk_exec, NULL, (void*)lmbd));
  }
  /* src: array */
  else if (strm_array_p(src)) {
    struct array_data *arrd = malloc(sizeof(struct array_data));
    arrd->arr = strm_value_ary(src);
    arrd->n = 0;
    src = strm_stream_value(strm_stream_new(strm_producer, arr_exec, NULL, (void*)arrd));
  }
  /* src: should be stream */

  /* dst: io */
  if (strm_io_p(dst)) {
    dst = strm_stream_value(strm_io_stream(dst, STRM_IO_WRITE));
  }
  /* dst: lambda */
  else if (strm_lambda_p(dst)) {
    struct strm_lambda* lmbd = strm_value_lambda(dst);
    dst = strm_stream_value(strm_stream_new(strm_filter, blk_exec, NULL, (void*)lmbd));
  }
  /* dst: cfunc */
  else if (strm_cfunc_p(dst)) {
    strm_cfunc func = strm_value_cfunc(dst);
    dst = strm_stream_value(strm_stream_new(strm_filter, cfunc_exec, cfunc_closer, func));
  }

  /* stream x stream */
  if (strm_stream_p(src) && strm_stream_p(dst)) {
    strm_stream* lstrm = strm_value_stream(src);
    strm_stream* rstrm = strm_value_stream(dst);
    if (lstrm == NULL || rstrm == NULL ||
        lstrm->mode == strm_consumer ||
        rstrm->mode == strm_producer) {
      strm_raise(strm, "stream error");
      return STRM_NG;
    }
    strm_stream_connect(strm_value_stream(src), strm_value_stream(dst));
    *ret = dst;
    return STRM_OK;
  }
  return STRM_NG;
}