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
typedef  int /*<<< orphan*/  strm_string ;
typedef  scalar_t__ strm_int ;

/* Variables and functions */
 scalar_t__ STRM_STR_INTERN_LIMIT ; 
 scalar_t__ readonly_data_p (char const*) ; 
 int /*<<< orphan*/  str_intern (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_new (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_event_loop_started ; 

strm_string
strm_str_new(const char* p, strm_int len)
{
  if (!strm_event_loop_started) {
    /* single thread mode */
    if (p && (len < STRM_STR_INTERN_LIMIT || readonly_data_p(p))) {
      return str_intern(p, len, 0);
    }
  }
  return str_new(p, len, 0);
}