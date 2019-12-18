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
struct _Locale_monetary {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _Locale_positive_sign (struct _Locale_monetary*) ; 
 int /*<<< orphan*/  const* _ToWChar (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

const wchar_t *_WLocale_positive_sign(struct _Locale_monetary *__loc, wchar_t *buf, size_t bufSize)
{ return _ToWChar(_Locale_positive_sign(__loc), buf, bufSize); }