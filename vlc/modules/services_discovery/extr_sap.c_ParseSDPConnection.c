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
struct sockaddr_storage {void* ss_len; void* ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
typedef  void* socklen_t ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  inet_pton (void*,char*,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned int*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int ParseSDPConnection (const char *str, struct sockaddr_storage *addr,
                               socklen_t *addrlen, unsigned *number)
{
    char host[60];
    unsigned fam, n1, n2;

    int res = sscanf (str, "IN IP%u %59[^/]/%u/%u", &fam, host, &n1, &n2);
    if (res < 2)
        return -1;

    switch (fam)
    {
#ifdef AF_INET6
        case 6:
            addr->ss_family = AF_INET6;
# ifdef HAVE_SA_LEN
            addr->ss_len =
# endif
           *addrlen = sizeof (struct sockaddr_in6);

            if (inet_pton (AF_INET6, host,
                           &((struct sockaddr_in6 *)addr)->sin6_addr) <= 0)
                return -1;

            *number = (res >= 3) ? n1 : 1;
            break;
#endif

        case 4:
            addr->ss_family = AF_INET;
# ifdef HAVE_SA_LEN
            addr->ss_len =
# endif
           *addrlen = sizeof (struct sockaddr_in);

            if (inet_pton (AF_INET, host,
                           &((struct sockaddr_in *)addr)->sin_addr) <= 0)
                return -1;

            *number = (res >= 4) ? n2 : 1;
            break;

        default:
            return -1;
    }
    return 0;
}