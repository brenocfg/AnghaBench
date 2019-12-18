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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int TZ_FAIL ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int parse_tz (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int time_alloc (struct timeval*,int,int /*<<< orphan*/ *) ; 
 int time_localoffset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
time_now(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct timeval tv;
  int utc_offset;

  if (argc == 0) {
    utc_offset = time_localoffset(0);
  }
  else {
    char *s;
    strm_int slen;

    strm_get_args(strm, argc, args, "s", &s, &slen);
    utc_offset = parse_tz(s, slen);
    if (utc_offset == TZ_FAIL) {
      strm_raise(strm, "wrong timezeone");
      return STRM_NG;
    }
  }
  gettimeofday(&tv, NULL);
  return time_alloc(&tv, utc_offset, ret);
}