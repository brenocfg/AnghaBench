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
typedef  char* LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  strcmpW (char*,char*) ; 

__attribute__((used)) static BOOL merge_type_match(LPCWSTR type1, LPCWSTR type2)
{
    if (((type1[0] == 'l') || (type1[0] == 's')) &&
        ((type2[0] == 'l') || (type2[0] == 's')))
        return TRUE;

    if (((type1[0] == 'L') || (type1[0] == 'S')) &&
        ((type2[0] == 'L') || (type2[0] == 'S')))
        return TRUE;

    return !strcmpW( type1, type2 );
}