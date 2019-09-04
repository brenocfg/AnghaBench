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
typedef  char* LPCWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 char* strchrW (char*,char) ; 
 int /*<<< orphan*/  strcmpiW (char*,char const*) ; 
 int strlenW (char*) ; 

__attribute__((used)) static BOOL domain_matches(LPCWSTR server, LPCWSTR domain)
{
    static const WCHAR localW[] = { '<','l','o','c','a','l','>',0 };
    BOOL ret = FALSE;

    if (!strcmpiW( domain, localW ) && !strchrW( server, '.' ))
        ret = TRUE;
    else if (*domain == '*')
    {
        if (domain[1] == '.')
        {
            LPCWSTR dot;

            /* For a hostname to match a wildcard, the last domain must match
             * the wildcard exactly.  E.g. if the wildcard is *.a.b, and the
             * hostname is www.foo.a.b, it matches, but a.b does not.
             */
            dot = strchrW( server, '.' );
            if (dot)
            {
                int len = strlenW( dot + 1 );

                if (len > strlenW( domain + 2 ))
                {
                    LPCWSTR ptr;

                    /* The server's domain is longer than the wildcard, so it
                     * could be a subdomain.  Compare the last portion of the
                     * server's domain.
                     */
                    ptr = dot + len + 1 - strlenW( domain + 2 );
                    if (!strcmpiW( ptr, domain + 2 ))
                    {
                        /* This is only a match if the preceding character is
                         * a '.', i.e. that it is a matching domain.  E.g.
                         * if domain is '*.b.c' and server is 'www.ab.c' they
                         * do not match.
                         */
                        ret = *(ptr - 1) == '.';
                    }
                }
                else
                    ret = !strcmpiW( dot + 1, domain + 2 );
            }
        }
    }
    else
        ret = !strcmpiW( server, domain );
    return ret;
}