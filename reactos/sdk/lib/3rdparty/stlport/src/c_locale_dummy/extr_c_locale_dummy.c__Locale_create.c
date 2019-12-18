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
 int _STLP_LOC_NO_PLATFORM_SUPPORT ; 

void* _Locale_create(const char* name, int *__err_code) {
  if (name[0] == 'C' && name[1] == 0)
  { return (void*)0x1; }
  *__err_code = _STLP_LOC_NO_PLATFORM_SUPPORT; return 0;
}