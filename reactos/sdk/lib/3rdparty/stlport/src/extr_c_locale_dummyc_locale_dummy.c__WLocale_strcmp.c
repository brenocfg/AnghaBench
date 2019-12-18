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
typedef  scalar_t__ wchar_t ;
struct _Locale_collate {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _STLP_WCSNCPY (scalar_t__*,int,scalar_t__ const*,size_t) ; 
 int wcscmp (scalar_t__*,scalar_t__*) ; 

int _WLocale_strcmp(struct _Locale_collate* lcol,
                    const wchar_t* s1, size_t n1, const wchar_t* s2, size_t n2) {
  int ret = 0;
  wchar_t buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    _STLP_WCSNCPY(buf1, 64, s1, bufsize1); buf1[bufsize1] = 0;
    _STLP_WCSNCPY(buf2, 64, s2, bufsize2); buf2[bufsize2] = 0;

    ret = wcscmp(buf1, buf2);
    if (ret != 0) return ret < 0 ? -1 : 1;
    s1 += bufsize1; n1 -= bufsize1;
    s2 += bufsize2; n2 -= bufsize2;
  }
  return ret == 0 ? 0 : (ret < 0 ? -1 : 1);
}