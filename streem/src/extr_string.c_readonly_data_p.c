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

/* Variables and functions */
 int /*<<< orphan*/  __init_array_start ; 
 char const* _etext ; 

__attribute__((used)) static inline int
readonly_data_p(const char* p)
{
  return _etext < p && p < (char*)&__init_array_start;
}