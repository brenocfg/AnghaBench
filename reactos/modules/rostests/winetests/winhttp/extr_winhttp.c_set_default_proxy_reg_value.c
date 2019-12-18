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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  IsWow64Process (int /*<<< orphan*/ ,scalar_t__*) ; 
 int KEY_WOW64_32KEY ; 
 int KEY_WOW64_64KEY ; 
 int KEY_WRITE ; 
 int /*<<< orphan*/  set_proxy (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_default_proxy_reg_value( BYTE *buf, DWORD len, DWORD type )
{
    BOOL wow64;
    IsWow64Process( GetCurrentProcess(), &wow64 );
    if (sizeof(void *) > sizeof(int) || wow64)
    {
        set_proxy( KEY_WRITE|KEY_WOW64_64KEY, buf, len, type );
        set_proxy( KEY_WRITE|KEY_WOW64_32KEY, buf, len, type );
    }
    else
        set_proxy( KEY_WRITE, buf, len, type );
}