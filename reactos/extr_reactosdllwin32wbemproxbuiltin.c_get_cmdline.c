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

/* Variables and functions */
 int /*<<< orphan*/  GetCommandLineW () ; 
 scalar_t__ GetCurrentProcessId () ; 
 int /*<<< orphan*/ * heap_strdupW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static WCHAR *get_cmdline( DWORD process_id )
{
    if (process_id == GetCurrentProcessId()) return heap_strdupW( GetCommandLineW() );
    return NULL; /* FIXME handle different process case */
}