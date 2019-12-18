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
struct cycle_data {scalar_t__ count; int /*<<< orphan*/  ary; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  scalar_t__ strm_int ;
typedef  int /*<<< orphan*/  strm_array ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fin_cycle ; 
 int /*<<< orphan*/  gen_cycle ; 
 struct cycle_data* malloc (int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_cycle(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_array a;
  strm_int n = -1;
  struct cycle_data *d;

  strm_get_args(strm, argc, args, "A|i", &a, &n);
  if (argc == 2 && n <= 0) {
    strm_raise(strm, "invalid count number");
    return STRM_NG;
  }
  d = malloc(sizeof(*d));
  d->ary = a;
  d->count = n;
  *ret = strm_stream_value(strm_stream_new(strm_producer, gen_cycle, fin_cycle, (void*)d));
  return STRM_OK;
}