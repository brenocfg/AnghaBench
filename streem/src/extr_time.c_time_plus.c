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
struct strm_time {int /*<<< orphan*/  utc_offset; int /*<<< orphan*/  tv; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 struct strm_time* get_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_to_timeval (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_value_float (int /*<<< orphan*/ ) ; 
 int time_alloc (struct timeval*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeradd (int /*<<< orphan*/ *,struct timeval*,struct timeval*) ; 

__attribute__((used)) static int
time_plus(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct strm_time* t1;
  struct timeval tv, tv2;

  if (argc != 2) {
    strm_raise(strm, "wrong # of arguments");
    return STRM_NG;
  }
  t1 = get_time(args[0]);
  if (!strm_number_p(args[1])) {
    strm_raise(strm, "number required");
    return STRM_NG;
  }
  num_to_timeval(strm_value_float(args[1]), &tv);
  timeradd(&t1->tv, &tv, &tv2);
  return time_alloc(&tv2, t1->utc_offset, ret);
}