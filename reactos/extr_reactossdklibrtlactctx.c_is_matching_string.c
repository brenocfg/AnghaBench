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
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL is_matching_string( const WCHAR *str1, const WCHAR *str2 )
{
    if (!str1) return !str2;
    return str2 && !strcmpiW( str1, str2 );
}