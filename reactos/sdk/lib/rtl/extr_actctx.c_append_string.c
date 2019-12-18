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
typedef  scalar_t__ WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  strcatW (scalar_t__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  strlenW (scalar_t__*) ; 

__attribute__((used)) static inline void append_string( WCHAR *buffer, const WCHAR *prefix, const WCHAR *str )
{
    WCHAR *p = buffer;

    if (!str) return;
    strcatW( buffer, prefix );
    p += strlenW(p);
    *p++ = '"';
    strcpyW( p, str );
    p += strlenW(p);
    *p++ = '"';
    *p = 0;
}