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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_env ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ kh_end (int /*<<< orphan*/ *) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strm_str_intern_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_intern_str (int /*<<< orphan*/ ) ; 

int
env_get(strm_env* env, strm_string name, strm_value* val)
{
  khiter_t k;

  if (!strm_str_intern_p(name)) {
    name = strm_str_intern_str(name);
  }
  k = kh_get(env, env, name);
  if (k == kh_end(env)) return STRM_NG;
  *val = kh_value(env, k);
  return STRM_OK;
}