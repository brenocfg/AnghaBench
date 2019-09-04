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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetComputerNameW (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  memicmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL is_local_machine( const WCHAR *name, DWORD len )
{
    WCHAR buf[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD buflen = ARRAY_SIZE(buf);

    if (!GetComputerNameW( buf, &buflen )) return FALSE;
    return len == buflen && !memicmpW( name, buf, buflen );
}