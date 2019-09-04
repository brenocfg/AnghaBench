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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  _Locale_collate_t ;

/* Variables and functions */
 int CSTR_EQUAL ; 
 int CSTR_LESS_THAN ; 
 int _WLocale_strcmp_aux (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 

int _WLocale_strcmp(_Locale_collate_t* lcol,
                    const wchar_t* s1, size_t n1,
                    const wchar_t* s2, size_t n2) {
  int result;
  result = _WLocale_strcmp_aux(lcol, s1, n1, s2, n2);
  return (result == CSTR_EQUAL) ? 0 : (result == CSTR_LESS_THAN) ? -1 : 1;
}