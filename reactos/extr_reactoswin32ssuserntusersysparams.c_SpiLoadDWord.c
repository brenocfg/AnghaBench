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
typedef  int /*<<< orphan*/  Result ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  RegReadUserSetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
INT
SpiLoadDWord(PCWSTR pwszKey, PCWSTR pwszValue, INT iValue)
{
    DWORD Result;
    if (!RegReadUserSetting(pwszKey, pwszValue, REG_DWORD, &Result, sizeof(Result)))
    {
        return iValue;
    }
    return Result;
}