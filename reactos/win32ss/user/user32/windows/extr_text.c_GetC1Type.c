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
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CT_CTYPE1 ; 
 int /*<<< orphan*/  GetStringTypeW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WORD
GetC1Type(WCHAR Ch)
{
    WORD CharType;

    if (! GetStringTypeW(CT_CTYPE1, &Ch, 1, &CharType))
    {
        return 0;
    }

    return CharType;
}