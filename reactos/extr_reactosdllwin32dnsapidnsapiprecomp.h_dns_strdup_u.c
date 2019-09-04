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

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline char *dns_strdup_u( const char *src )
{
    char *dst;

    if (!src) return NULL;
    dst = HeapAlloc(GetProcessHeap(), 0, (strlen( src ) + 1) * sizeof(char) );
    if (dst) strcpy( dst, src );
    return dst;
}