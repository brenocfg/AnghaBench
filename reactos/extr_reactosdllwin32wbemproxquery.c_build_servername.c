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
struct view {scalar_t__ proplist; } ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GetComputerNameW (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/ * SysAllocString (scalar_t__*) ; 
 scalar_t__ toupperW (scalar_t__) ; 

__attribute__((used)) static BSTR build_servername( const struct view *view )
{
    WCHAR server[MAX_COMPUTERNAME_LENGTH + 1], *p;
    DWORD len = ARRAY_SIZE( server );

    if (view->proplist) return NULL;

    if (!(GetComputerNameW( server, &len ))) return NULL;
    for (p = server; *p; p++) *p = toupperW( *p );
    return SysAllocString( server );
}