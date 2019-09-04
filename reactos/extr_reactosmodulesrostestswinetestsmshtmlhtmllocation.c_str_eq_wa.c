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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpA (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int str_eq_wa(LPCWSTR strw, const char *stra)
{
    CHAR buf[512];

    if(!strw || !stra)
        return (void*)strw == (void*)stra;

    WideCharToMultiByte(CP_ACP, 0, strw, -1, buf, sizeof(buf), NULL, NULL);
    return !lstrcmpA(stra, buf);
}