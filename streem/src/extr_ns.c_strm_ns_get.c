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
typedef  scalar_t__ strm_string ;
typedef  int /*<<< orphan*/  strm_state ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/ * kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ns ; 
 int /*<<< orphan*/  nstbl ; 

strm_state*
strm_ns_get(strm_string name)
{
  khiter_t k;

  if (!nstbl) return NULL;
  k = kh_get(ns, nstbl, (intptr_t)name);
  if (k == kh_end(nstbl)) return NULL;
  return kh_value(nstbl, k);
}