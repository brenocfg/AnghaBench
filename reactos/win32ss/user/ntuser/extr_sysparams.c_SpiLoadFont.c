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
typedef  int /*<<< orphan*/ * PLOGFONTW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_METRIC ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  RegReadUserSetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
VOID
SpiLoadFont(PLOGFONTW plfOut, LPWSTR pwszValueName, PLOGFONTW plfDefault)
{
    BOOL bResult;

    bResult = RegReadUserSetting(KEY_METRIC,
                                 pwszValueName,
                                 REG_BINARY,
                                 plfOut,
                                 sizeof(LOGFONTW));
    if (!bResult)
        *plfOut = *plfDefault;
}