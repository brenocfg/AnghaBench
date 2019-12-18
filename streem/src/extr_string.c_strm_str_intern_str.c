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

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_intern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_event_loop_started ; 
 scalar_t__ strm_str_intern_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_mutex ; 

strm_string
strm_str_intern_str(strm_string str)
{
  if (strm_str_intern_p(str)) {
    return str;
  }
  if (!strm_event_loop_started) {
    return str_intern(strm_str_ptr(str), strm_str_len(str), 0);
  }
  pthread_mutex_lock(&sym_mutex);
  str = str_intern(strm_str_ptr(str), strm_str_len(str), 0);
  pthread_mutex_unlock(&sym_mutex);

  return str;
}