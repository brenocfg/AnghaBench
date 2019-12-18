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
struct timeval {int dummy; } ;
struct strm_time {int /*<<< orphan*/  tv; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 struct strm_time* get_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_float_value (double) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 double strm_value_float (int /*<<< orphan*/ ) ; 
 int time_plus (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timersub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 double timeval_to_num (struct timeval*) ; 

__attribute__((used)) static int
time_minus(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct strm_time *t1;
  struct strm_time *t2;
  struct timeval tv;
  double d;

  if (argc != 2) {
    strm_raise(strm, "wrong # of arguments");
    return STRM_NG;
  }
  if (strm_number_p(args[1])) {
    d = strm_value_float(args[1]);
    args[1] = strm_float_value(-d);
    return time_plus(strm, argc, args, ret);
  }
  t1 = get_time(args[0]);
  t2 = get_time(args[1]);
  timersub(&t1->tv, &t2->tv, &tv);
  d = timeval_to_num(&tv);
  *ret = strm_float_value(d);
  return STRM_OK;
}