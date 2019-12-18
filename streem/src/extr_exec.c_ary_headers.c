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
typedef  size_t strm_int ;
typedef  int /*<<< orphan*/  strm_array ;
typedef  int /*<<< orphan*/  node_string ;

/* Variables and functions */
 int /*<<< orphan*/  node_to_sym (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * strm_ary_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_array
ary_headers(node_string* headers, strm_int len)
{
  strm_array ary = strm_ary_new(NULL, len);
  strm_value* p = strm_ary_ptr(ary);
  strm_int i;

  for (i=0; i<len; i++) {
    p[i] = node_to_sym(headers[i]);
  }
  return ary;
}