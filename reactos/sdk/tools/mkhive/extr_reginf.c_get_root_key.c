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
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BCD ; 
 int /*<<< orphan*/  BCDPath ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKCR ; 
 int /*<<< orphan*/  HKCRPath ; 
 int /*<<< orphan*/  HKCU ; 
 int /*<<< orphan*/  HKCUPath ; 
 int /*<<< orphan*/  HKLM ; 
 int /*<<< orphan*/  HKLMPath ; 
 int /*<<< orphan*/  HKR ; 
 int /*<<< orphan*/  HKU ; 
 int /*<<< orphan*/  HKUPath ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
get_root_key(PWCHAR Name)
{
    if (!strcmpiW(Name, HKCR))
    {
        strcpyW(Name, HKCRPath);
        return TRUE;
    }

    if (!strcmpiW(Name, HKCU))
    {
        strcpyW(Name, HKCUPath);
        return TRUE;
    }

    if (!strcmpiW(Name, HKLM))
    {
        strcpyW(Name, HKLMPath);
        return TRUE;
    }

    if (!strcmpiW(Name, HKU))
    {
        strcpyW(Name, HKUPath);
        return TRUE;
    }

    if (!strcmpiW(Name, BCD))
    {
        strcpyW(Name, BCDPath);
        return TRUE;
    }

#if 0
    if (!strcmpiW(Name, HKR))
        return FALSE;
#endif

  return FALSE;
}