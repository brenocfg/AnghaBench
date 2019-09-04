#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_collate_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int CSTR_EQUAL ; 
 int CompareStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ trim_size_t_to_DWORD (size_t) ; 

__attribute__((used)) static int _WLocale_strcmp_aux(_Locale_collate_t* lcol,
                               const wchar_t* s1, size_t n1,
                               const wchar_t* s2, size_t n2) {
  int result = CSTR_EQUAL;
  while (n1 > 0 || n2 > 0) {
    DWORD size1 = trim_size_t_to_DWORD(n1);
    DWORD size2 = trim_size_t_to_DWORD(n2);
    result = CompareStringW(lcol->lc.id, 0, s1, size1, s2, size2);
    if (result != CSTR_EQUAL)
      break;
    n1 -= size1;
    n2 -= size2;
  }
  return result;
}