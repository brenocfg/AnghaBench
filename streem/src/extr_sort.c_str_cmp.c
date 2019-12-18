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
typedef  scalar_t__ strm_int ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strm_str_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_str_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
str_cmp(strm_value x, strm_value y)
{
  strm_string a = strm_value_str(x);
  strm_string b = strm_value_str(y);
  strm_int alen = strm_str_len(a);
  strm_int blen = strm_str_len(b);
  strm_int len, cmp;

  if (alen > blen) {
    len = blen;
  }
  else {
    len = alen;
  }
  cmp = memcmp(strm_str_ptr(a), strm_str_ptr(b), len);
  if (cmp == 0) {
    if (alen > len) return 1;
    if (blen > len) return -1;
  }
  return cmp;
}