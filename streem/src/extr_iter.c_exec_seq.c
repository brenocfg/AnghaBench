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
struct seq_data {double n; double inc; double end; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  gen_seq ; 
 struct seq_data* malloc (int) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,double*,double*,double*) ; 
 int /*<<< orphan*/  strm_producer ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_seq(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  double start=1, end=-1, inc=1, tmp;
  struct seq_data* d;

  strm_get_args(strm, argc, args, "|fff", &start, &end, &tmp);
  switch (argc) {
  case 1:
    end = start;
    start = 1;
    break;
  case 3:
    inc = end;
    end = tmp;
    break;
  default:
    break;
  }
  d = malloc(sizeof(*d));
  d->n = start;
  d->inc = inc;
  d->end = end;
  *ret = strm_stream_value(strm_stream_new(strm_producer, gen_seq, NULL, (void*)d));
  return STRM_OK;
}