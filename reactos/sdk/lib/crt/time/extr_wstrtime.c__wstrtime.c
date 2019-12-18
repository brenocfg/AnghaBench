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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 

wchar_t* _wstrtime(wchar_t* time)
{
   static const WCHAR format[] = { 'H','H','\'',':','\'','m','m','\'',':','\'','s','s',0 };

   GetTimeFormatW(LOCALE_NEUTRAL, 0, NULL, format, (LPWSTR)time, 9);

   return time;
}