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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  test_gethostbyaddr2_r (void*,char const*,void const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_gethostbyaddr_r (void*,char const*,void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_byaddr(void *handle,
                        const char *module,
                        const void* addr, socklen_t len,
                        int af) {
        test_gethostbyaddr2_r(handle, module, addr, len, af);
        puts("");

        test_gethostbyaddr_r(handle, module, addr, len, af);
        puts("");
}