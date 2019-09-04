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
typedef  enum platform { ____Placeholder_platform } platform ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int PLATFORM_ARM ; 
 int PLATFORM_INTEL ; 
 int PLATFORM_INTEL64 ; 
 int PLATFORM_UNKNOWN ; 
 int PLATFORM_X64 ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szAMD64 ; 
 int /*<<< orphan*/  szARM ; 
 int /*<<< orphan*/  szIntel ; 
 int /*<<< orphan*/  szIntel64 ; 
 int /*<<< orphan*/  szX64 ; 

__attribute__((used)) static enum platform parse_platform( const WCHAR *str )
{
    if (!str[0] || !strcmpW( str, szIntel )) return PLATFORM_INTEL;
    else if (!strcmpW( str, szIntel64 )) return PLATFORM_INTEL64;
    else if (!strcmpW( str, szX64 ) || !strcmpW( str, szAMD64 )) return PLATFORM_X64;
    else if (!strcmpW( str, szARM )) return PLATFORM_ARM;
    return PLATFORM_UNKNOWN;
}