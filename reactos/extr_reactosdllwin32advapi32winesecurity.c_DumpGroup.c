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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/  PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DumpSid (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpString (char const*,int,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetSecurityDescriptorGroup (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL DumpGroup(PSECURITY_DESCRIPTOR SecurityDescriptor, WCHAR **pwptr, ULONG *plen)
{
    static const WCHAR prefix[] = {'G',':',0};
    BOOL bDefaulted;
    PSID psid;

    if (!GetSecurityDescriptorGroup(SecurityDescriptor, &psid, &bDefaulted))
        return FALSE;

    if (psid == NULL)
        return TRUE;

    DumpString(prefix, -1, pwptr, plen);
    if (!DumpSid(psid, pwptr, plen))
        return FALSE;
    return TRUE;
}