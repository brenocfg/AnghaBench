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
typedef  int /*<<< orphan*/  stra2 ;
typedef  int /*<<< orphan*/  stra1 ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrcmpA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int strcmp_ww(LPCWSTR strw1, LPCWSTR strw2)
{
    CHAR stra1[512], stra2[512];
    WideCharToMultiByte(CP_ACP, 0, strw1, -1, stra1, sizeof(stra1), NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0, strw2, -1, stra2, sizeof(stra2), NULL, NULL);
    return lstrcmpA(stra1, stra2);
}