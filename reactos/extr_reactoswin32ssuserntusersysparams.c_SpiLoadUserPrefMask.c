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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_DESKTOP ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  RegReadUserSetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VAL_USERPREFMASK ; 

__attribute__((used)) static
DWORD
SpiLoadUserPrefMask(DWORD dValue)
{
    DWORD Result;
    if (!RegReadUserSetting(KEY_DESKTOP, VAL_USERPREFMASK, REG_BINARY, &Result, sizeof(Result)))
    {
        return dValue;
    }
    return Result;
}