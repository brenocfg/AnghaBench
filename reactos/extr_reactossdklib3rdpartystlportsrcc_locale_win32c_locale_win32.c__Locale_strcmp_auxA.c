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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_collate_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int CSTR_EQUAL ; 
 int CompareStringA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,char const*,scalar_t__) ; 
 scalar_t__ trim_size_t_to_DWORD (size_t) ; 

__attribute__((used)) static int _Locale_strcmp_auxA(_Locale_collate_t* lcol,
                               const char* s1, size_t n1,
                               const char* s2, size_t n2) {
  int result = CSTR_EQUAL;
  while (n1 > 0 || n2 > 0) {
    DWORD size1 = trim_size_t_to_DWORD(n1);
    DWORD size2 = trim_size_t_to_DWORD(n2);
    result = CompareStringA(lcol->lc.id, 0, s1, size1, s2, size2);
    if (result != CSTR_EQUAL)
      break;
    n1 -= size1;
    n2 -= size2;
  }
  return result;
}