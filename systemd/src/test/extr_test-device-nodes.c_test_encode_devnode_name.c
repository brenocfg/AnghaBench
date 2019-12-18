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
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_encoded_as (char*,char*) ; 

__attribute__((used)) static void test_encode_devnode_name(void) {
        assert_se(expect_encoded_as("systemd sucks", "systemd\\x20sucks"));
        assert_se(expect_encoded_as("pinkiepie", "pinkiepie"));
        assert_se(expect_encoded_as("valíd\\ųtf8", "valíd\\x5cųtf8"));
        assert_se(expect_encoded_as("s/ash/ng", "s\\x2fash\\x2fng"));
        assert_se(expect_encoded_as("/", "\\x2f"));
        assert_se(expect_encoded_as("!", "\\x21"));
}