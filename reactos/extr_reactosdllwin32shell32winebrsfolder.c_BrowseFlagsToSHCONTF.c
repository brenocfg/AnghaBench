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
typedef  int UINT ;
typedef  int DWORD ;

/* Variables and functions */
 int BIF_BROWSEINCLUDEFILES ; 
 int SHCONTF_FOLDERS ; 
 int SHCONTF_NONFOLDERS ; 

__attribute__((used)) static inline DWORD BrowseFlagsToSHCONTF(UINT ulFlags)
{
    return SHCONTF_FOLDERS | (ulFlags & BIF_BROWSEINCLUDEFILES ? SHCONTF_NONFOLDERS : 0);
}