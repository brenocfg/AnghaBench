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
struct concat_data {int len; int /*<<< orphan*/ ** latch; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  concat_start ; 
 struct concat_data* malloc (int) ; 
 int /*<<< orphan*/  strm_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strm_latch_new () ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct concat_data*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
exec_concat(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct concat_data* d = malloc(sizeof(struct concat_data)+sizeof(strm_stream*)*argc);
  strm_int i;
  strm_stream* s;

  d->i = 0;
  d->len = argc;
  for (i=0; i<argc; i++) {
    strm_value r;
    s = strm_latch_new();
    strm_connect(strm, args[i], strm_stream_value(s), &r);
    d->latch[i] = s;
  }
  *ret = strm_stream_value(strm_stream_new(strm_producer, concat_start, NULL, d));
  return STRM_OK;
}