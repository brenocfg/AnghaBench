#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {scalar_t__ cp; int /*<<< orphan*/  mbtowc_flags; int /*<<< orphan*/  cleads; } ;
typedef  TYPE_1__ _Locale_codecvt_t ;

/* Variables and functions */
 scalar_t__ CP_UTF7 ; 
 scalar_t__ CP_UTF8 ; 
#define  ERROR_NO_UNICODE_TRANSLATION 128 
 int GetLastError () ; 
 int MultiByteToWideChar (scalar_t__,int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __isleadbyte (char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mbtowc(_Locale_codecvt_t *l, wchar_t *dst, const char *from, unsigned int count) {
  int result;

  if (l->cp == CP_UTF7 || l->cp == CP_UTF8) {
    result = MultiByteToWideChar(l->cp, l->mbtowc_flags, from, count, dst, 1);
    if (result == 0) {
      switch (GetLastError()) {
        case ERROR_NO_UNICODE_TRANSLATION:
          return -2;
        default:
          return -1;
      }
    }
  }
  else {
    if (count == 1 && __isleadbyte(*from, l->cleads)) return (size_t)-2;
    result = MultiByteToWideChar(l->cp, l->mbtowc_flags, from, count, dst, 1);
    if (result == 0) return -1;
  }

  return result;
}