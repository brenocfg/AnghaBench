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
struct strm_misc {int /*<<< orphan*/ * ns; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_state ;

/* Variables and functions */
 scalar_t__ STRM_PTR_AUX ; 
 scalar_t__ STRM_TAG_PTR ; 
 scalar_t__ strm_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ary_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_array ; 
 int /*<<< orphan*/ * strm_ns_number ; 
 int /*<<< orphan*/ * strm_ns_string ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 struct strm_misc* strm_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_ptr_type (struct strm_misc*) ; 
 scalar_t__ strm_string_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_value_tag (int /*<<< orphan*/ ) ; 

strm_state*
strm_value_ns(strm_value val)
{
  if (strm_array_p(val)) {
    strm_state* ns = strm_ary_ns(val);
    if (ns) return ns;
    return strm_ns_array;
  }
  if (strm_string_p(val)) {
    return strm_ns_string;
  }
  if (strm_number_p(val)) {
    return strm_ns_number;
  }
  if (strm_value_tag(val) == STRM_TAG_PTR) {
    struct strm_misc* p = strm_ptr(val);

    if (!p) return NULL;
    if (strm_ptr_type(p) == STRM_PTR_AUX) {
      return p->ns;
    }
  }
  return NULL;
}