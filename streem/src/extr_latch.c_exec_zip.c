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
struct zip_data {int len; int /*<<< orphan*/ ** latch; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int STRM_OK ; 
 struct zip_data* malloc (int) ; 
 int /*<<< orphan*/  strm_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strm_latch_new () ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zip_data*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zip_close ; 
 int /*<<< orphan*/  zip_start ; 

__attribute__((used)) static int
exec_zip(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct zip_data* z = malloc(sizeof(struct zip_data)+sizeof(strm_stream*)*argc);
  strm_int i;
  strm_stream* s;

  z->i = 0;
  z->len = argc;
  for (i=0; i<argc; i++) {
    strm_value r;
    s = strm_latch_new();
    strm_connect(strm, args[i], strm_stream_value(s), &r);
    z->latch[i] = s;
  }
  *ret = strm_stream_value(strm_stream_new(strm_producer, zip_start, zip_close, z));
  return STRM_OK;
}