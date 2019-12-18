#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tv_usec; } ;
struct strm_time {TYPE_1__ tv; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 struct strm_time* get_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_int_value (int) ; 

__attribute__((used)) static int
time_nanosec(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_value time;
  struct strm_time *t;

  strm_get_args(strm, argc, args, "v", &time);
  t = get_time(time);
  *ret = strm_int_value(t->tv.tv_usec*1000);
  return STRM_OK;
}