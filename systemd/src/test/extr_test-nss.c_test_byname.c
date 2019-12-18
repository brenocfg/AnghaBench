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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  test_gethostbyname2_r (void*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_gethostbyname3_r (void*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_gethostbyname4_r (void*,char const*,char const*) ; 
 int /*<<< orphan*/  test_gethostbyname_r (void*,char const*,char const*) ; 

__attribute__((used)) static void test_byname(void *handle, const char *module, const char *name) {
        test_gethostbyname4_r(handle, module, name);
        puts("");

        test_gethostbyname3_r(handle, module, name, AF_INET);
        puts("");
        test_gethostbyname3_r(handle, module, name, AF_INET6);
        puts("");
        test_gethostbyname3_r(handle, module, name, AF_UNSPEC);
        puts("");
        test_gethostbyname3_r(handle, module, name, AF_LOCAL);
        puts("");

        test_gethostbyname2_r(handle, module, name, AF_INET);
        puts("");
        test_gethostbyname2_r(handle, module, name, AF_INET6);
        puts("");
        test_gethostbyname2_r(handle, module, name, AF_UNSPEC);
        puts("");
        test_gethostbyname2_r(handle, module, name, AF_LOCAL);
        puts("");

        test_gethostbyname_r(handle, module, name);
        puts("");
}