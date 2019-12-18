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
typedef  int /*<<< orphan*/  strm_kvs ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 scalar_t__ strm_value_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static strm_kvs*
get_kvs(int argc, strm_value* args)
{
  if (argc == 0) return NULL;
  return (strm_kvs*)strm_value_ptr(args[0], STRM_PTR_AUX);
}