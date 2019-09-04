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
typedef  int /*<<< orphan*/  const wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ lc; } ;
typedef  TYPE_2__ _Locale_monetary_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  LOCALE_SPOSITIVESIGN ; 

const wchar_t* _WLocale_positive_sign(_Locale_monetary_t * lmon, wchar_t* buf, size_t bufSize)
{ GetLocaleInfoW(lmon->lc.id, LOCALE_SPOSITIVESIGN, buf, (int)bufSize); return buf; }