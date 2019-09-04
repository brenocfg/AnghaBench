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
 int FALSE ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int lstrlenW (char*) ; 

__attribute__((used)) static BOOL domain_name_matches(LPCWSTR constraint, LPCWSTR name)
{
    BOOL match;

    /* RFC 5280, section 4.2.1.10:
     * "For URIs, the constraint applies to the host part of the name...
     *  When the constraint begins with a period, it MAY be expanded with one
     *  or more labels.  That is, the constraint ".example.com" is satisfied by
     *  both host.example.com and my.host.example.com.  However, the constraint
     *  ".example.com" is not satisfied by "example.com".  When the constraint
     *  does not begin with a period, it specifies a host."
     * and for email addresses,
     * "To indicate all Internet mail addresses on a particular host, the
     *  constraint is specified as the host name.  For example, the constraint
     *  "example.com" is satisfied by any mail address at the host
     *  "example.com".  To specify any address within a domain, the constraint
     *  is specified with a leading period (as with URIs)."
     */
    if (constraint[0] == '.')
    {
        /* Must be strictly greater than, a name can't begin with '.' */
        if (lstrlenW(name) > lstrlenW(constraint))
            match = !lstrcmpiW(name + lstrlenW(name) - lstrlenW(constraint),
             constraint);
        else
        {
            /* name is too short, no match */
            match = FALSE;
        }
    }
    else
        match = !lstrcmpiW(name, constraint);
     return match;
}