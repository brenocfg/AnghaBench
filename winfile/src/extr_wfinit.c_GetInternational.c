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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTOF (scalar_t__) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_SDECIMAL ; 
 int /*<<< orphan*/  LOCALE_STHOUSAND ; 
 int /*<<< orphan*/  lcid ; 
 scalar_t__ szComma ; 
 scalar_t__ szDecimal ; 

VOID
GetInternational()
{
   GetLocaleInfoW(lcid, LOCALE_STHOUSAND, (LPWSTR) szComma, COUNTOF(szComma));
   GetLocaleInfoW(lcid, LOCALE_SDECIMAL, (LPWSTR) szDecimal, COUNTOF(szDecimal));
}