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
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_TRUST_INVALID_NAME_CONSTRAINTS ; 
 int FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__) ; 
 int domain_name_matches (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lstrcmpiW (scalar_t__,scalar_t__) ; 
 scalar_t__ strchrW (scalar_t__,char) ; 

__attribute__((used)) static BOOL rfc822_name_matches(LPCWSTR constraint, LPCWSTR name,
 DWORD *trustErrorStatus)
{
    BOOL match = FALSE;
    LPCWSTR at;

    TRACE("%s, %s\n", debugstr_w(constraint), debugstr_w(name));

    if (!constraint)
        *trustErrorStatus |= CERT_TRUST_INVALID_NAME_CONSTRAINTS;
    else if (!name)
        ; /* no match */
    else if (strchrW(constraint, '@'))
        match = !lstrcmpiW(constraint, name);
    else
    {
        if ((at = strchrW(name, '@')))
            match = domain_name_matches(constraint, at + 1);
        else
            match = !lstrcmpiW(constraint, name);
    }
    return match;
}