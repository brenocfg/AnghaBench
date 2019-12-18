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
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 scalar_t__ strm_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_number_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static strm_value
convert_number(strm_stream* strm, strm_value data, strm_value func)
{
  strm_value val;

  if (strm_funcall(strm, func, 1, &data, &val) == STRM_NG) {
    return strm_nil_value();
  }
  if (!strm_number_p(val)) {
    strm_raise(strm, "number required");
    return strm_nil_value();
  }
  return val;
}