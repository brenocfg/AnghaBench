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
typedef  char wchar_t ;
struct _Locale_numeric {int dummy; } ;

/* Variables and functions */

const wchar_t * _WLocale_false(struct _Locale_numeric* lnum, wchar_t* buf, size_t bufSize)
{ return L"false"; }