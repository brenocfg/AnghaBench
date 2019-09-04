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
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dns_strdup_aw (int /*<<< orphan*/ ) ; 
 char* dns_strdup_wu (scalar_t__) ; 

__attribute__((used)) static inline char *dns_strdup_au( LPCSTR src )
{
    char *dst = NULL;
    LPWSTR ret = dns_strdup_aw( src );

    if (ret)
    {
        dst = dns_strdup_wu( ret );
        HeapFree( GetProcessHeap(), 0, ret );
    }
    return dst;
}