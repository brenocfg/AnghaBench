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
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  CharUpperW (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline LPWSTR str_dup_upper( LPCWSTR str )
{
    INT len = (strlenW(str) + 1) * sizeof(WCHAR);
    LPWSTR p = HeapAlloc( GetProcessHeap(), 0, len );
    if (p)
    {
        memcpy( p, str, len );
        CharUpperW( p );
    }
    return p;
}