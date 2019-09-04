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
typedef  int /*<<< orphan*/  awcBuffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RegReadUserSetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _wtoi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
INT
SpiLoadInt(PCWSTR pwszKey, PCWSTR pwszValue, INT iValue)
{
    WCHAR awcBuffer[12];
    ULONG cbSize;

    cbSize = sizeof(awcBuffer);
    if (!RegReadUserSetting(pwszKey, pwszValue, REG_SZ, awcBuffer, cbSize))
    {
        return iValue;
    }
    return _wtoi(awcBuffer);
}