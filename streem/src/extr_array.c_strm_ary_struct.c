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
struct strm_array {int dummy; } ;
typedef  int /*<<< orphan*/  strm_value ;

/* Variables and functions */
 scalar_t__ strm_value_vptr (int /*<<< orphan*/ ) ; 

struct strm_array*
strm_ary_struct(strm_value v)
{
  return (struct strm_array*)strm_value_vptr(v);
}