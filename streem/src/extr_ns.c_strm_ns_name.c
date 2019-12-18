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
typedef  int /*<<< orphan*/  strm_state ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 scalar_t__ kh_begin (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_exist (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kh_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nstbl ; 
 int /*<<< orphan*/  strm_str_null ; 

strm_string
strm_ns_name(strm_state* state)
{
  khiter_t k;

  if (!nstbl) return strm_str_null;
  for (k = kh_begin(nstbl); k != kh_end(nstbl); ++k) {
    if (kh_exist(nstbl, k)) {
      if (kh_value(nstbl, k) == state)
        return kh_key(nstbl, k);
    }
  }
  return strm_str_null;
}