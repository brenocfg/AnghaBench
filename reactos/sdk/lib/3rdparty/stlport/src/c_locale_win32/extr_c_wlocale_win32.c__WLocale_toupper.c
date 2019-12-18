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
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_ctype_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCMAP_UPPERCASE ; 
 int /*<<< orphan*/  LCMapStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

wint_t _WLocale_toupper(_Locale_ctype_t* ltype, wint_t c) {
  wchar_t in_c = c;
  wchar_t res;

  LCMapStringW(ltype->lc.id, LCMAP_UPPERCASE, &in_c, 1, &res, 1);
  return res;
}