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
 int UINT64_C (int) ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  test_format_bytes_one (int,int,char*,char*,char*,char*) ; 

__attribute__((used)) static void test_format_bytes(void) {
        test_format_bytes_one(900, true, "900B", "900B", "900B", "900B");
        test_format_bytes_one(900, false, "900", "900", "900", "900");
        test_format_bytes_one(1023, true, "1023B", "1023B", "1.0K", "1K");
        test_format_bytes_one(1023, false, "1023", "1023", "1.0K", "1K");
        test_format_bytes_one(1024, true, "1.0K", "1K", "1.0K", "1K");
        test_format_bytes_one(1024, false, "1.0K", "1K", "1.0K", "1K");
        test_format_bytes_one(1100, true, "1.0K", "1K", "1.1K", "1K");
        test_format_bytes_one(1500, true, "1.4K", "1K", "1.5K", "1K");
        test_format_bytes_one(UINT64_C(3)*1024*1024, true, "3.0M", "3M", "3.1M", "3M");
        test_format_bytes_one(UINT64_C(3)*1024*1024*1024, true, "3.0G", "3G", "3.2G", "3G");
        test_format_bytes_one(UINT64_C(3)*1024*1024*1024*1024, true, "3.0T", "3T", "3.2T", "3T");
        test_format_bytes_one(UINT64_C(3)*1024*1024*1024*1024*1024, true, "3.0P", "3P", "3.3P", "3P");
        test_format_bytes_one(UINT64_C(3)*1024*1024*1024*1024*1024*1024, true, "3.0E", "3E", "3.4E", "3E");
        test_format_bytes_one(UINT64_MAX, true, NULL, NULL, NULL, NULL);
        test_format_bytes_one(UINT64_MAX, false, NULL, NULL, NULL, NULL);
}