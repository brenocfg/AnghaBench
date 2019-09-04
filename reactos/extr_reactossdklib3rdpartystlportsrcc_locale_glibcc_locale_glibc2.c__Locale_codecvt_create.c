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
struct _Locale_name_hint {int dummy; } ;
struct _Locale_codecvt {int dummy; } ;

/* Variables and functions */
 int _STLP_LOC_NO_PLATFORM_SUPPORT ; 

struct _Locale_codecvt *_Locale_codecvt_create(const char *nm, struct _Locale_name_hint* hint,
                                               int *__err_code) {
  // Glibc do not support multibyte manipulation for the moment, it simply implements "C".
  if (nm[0] == 'C' && nm[1] == 0)
  { return (struct _Locale_codecvt*)0x01; }
  *__err_code = _STLP_LOC_NO_PLATFORM_SUPPORT; return 0;
}