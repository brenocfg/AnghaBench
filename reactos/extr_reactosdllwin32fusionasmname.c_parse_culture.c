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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {void* culture; } ;
typedef  int /*<<< orphan*/  const* LPCWSTR ;
typedef  TYPE_1__ IAssemblyNameImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 void* strdupW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static HRESULT parse_culture(IAssemblyNameImpl *name, LPCWSTR culture)
{
    static const WCHAR empty[] = {0};

    if (lstrlenW(culture) == 2)
        name->culture = strdupW(culture);
    else
        name->culture = strdupW(empty);

    return S_OK;
}