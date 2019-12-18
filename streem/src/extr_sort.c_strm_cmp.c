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

/* Variables and functions */
 int num_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int str_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_string_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
strm_cmp(strm_value a, strm_value b)
{
  if (strm_number_p(a)) {
    if (strm_number_p(b)) {
      return num_cmp(a,b);
    }
    return -1;
  }
  if (strm_string_p(a)) {
    if (strm_string_p(b)) {
      return str_cmp(a,b);
    }
    if (strm_number_p(b)) {
      return 1;
    }
    return 1;
  }
  return 1;
}