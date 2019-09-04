#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  value; scalar_t__ wstr; } ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ACEFLAG ;

/* Variables and functions */
 TYPE_1__* AceType ; 
 int strlenW (scalar_t__) ; 
 scalar_t__ strncmpW (scalar_t__,char*,int) ; 

__attribute__((used)) static BYTE ParseAceStringType(LPCWSTR* StringAcl)
{
    UINT len = 0;
    LPCWSTR szAcl = *StringAcl;
    const ACEFLAG *lpaf = AceType;

    while (*szAcl == ' ')
        szAcl++;

    while (lpaf->wstr &&
        (len = strlenW(lpaf->wstr)) &&
        strncmpW(lpaf->wstr, szAcl, len))
        lpaf++;

    if (!lpaf->wstr)
        return 0;

    *StringAcl = szAcl + len;
    return lpaf->value;
}