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
struct repeat_data {scalar_t__ count; int /*<<< orphan*/  v; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  scalar_t__ strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fin_repeat ; 
 int /*<<< orphan*/  gen_repeat ; 
 struct repeat_data* malloc (int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_repeat(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value v;
  strm_int n = -1;
  struct repeat_data *d;

  strm_get_args(strm, argc, args, "v|i", &v, &n);
  if (argc == 2 && n <= 0) {
    strm_raise(strm, "invalid count number");
    return STRM_NG;
  }
  d = malloc(sizeof(*d));
  d->v = v;
  d->count = n;
  *ret = strm_stream_value(strm_stream_new(strm_producer, gen_repeat, fin_repeat, (void*)d));
  return STRM_OK;
}