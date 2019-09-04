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
 int /*<<< orphan*/  GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 

wchar_t* _wstrdate(wchar_t* date)
{
   static const WCHAR format[] = { 'M','M','\'','/','\'','d','d','\'','/','\'','y','y',0 };

   GetDateFormatW(LOCALE_NEUTRAL, 0, NULL, format, (LPWSTR)date, 9);

   return date;

}