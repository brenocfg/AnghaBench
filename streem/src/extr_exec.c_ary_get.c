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
struct strm_array {size_t len; int /*<<< orphan*/ * ptr; scalar_t__ headers; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  size_t strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/ * strm_ary_ptr (scalar_t__) ; 
 struct strm_array* strm_ary_struct (int /*<<< orphan*/ ) ; 
 scalar_t__ strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strm_str_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strm_string_p (int /*<<< orphan*/ ) ; 
 size_t strm_value_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_value_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ary_get(strm_stream* strm, strm_value ary, int argc, strm_value* argv, strm_value* ret)
{
  struct strm_array* a;
  strm_value idx;

  if (argc != 1) {
    strm_raise(strm, "wrong number of arguments");
    return STRM_NG;
  }

  a = strm_ary_struct(ary);
  idx = argv[0];
  if (strm_number_p(idx)) {
    strm_int i = strm_value_int(idx);

    if (i>=a->len)
      return STRM_NG;
    *ret = a->ptr[i];
    return STRM_OK;
  }
  if (strm_string_p(idx)) {
    if (a->headers) {
      strm_int i, len = a->len;

      for (i=0; i<len; i++) {
        if (strm_str_eq(strm_value_str(idx),
                        strm_value_str(strm_ary_ptr(a->headers)[i]))) {
          *ret = a->ptr[i];
          return STRM_OK;
        }
      }
    }
  }
  return STRM_NG;
}