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
typedef  int /*<<< orphan*/  strm_int ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  str_intern (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_event_loop_started ; 
 int /*<<< orphan*/  sym_mutex ; 

strm_string
strm_str_intern(const char* p, strm_int len)
{
  strm_string str;

  assert(p!=NULL);
  if (!strm_event_loop_started) {
    return str_intern(p, len, 0);
  }
  pthread_mutex_lock(&sym_mutex);
  str = str_intern(p, len, 0);
  pthread_mutex_unlock(&sym_mutex);

  return str;
}