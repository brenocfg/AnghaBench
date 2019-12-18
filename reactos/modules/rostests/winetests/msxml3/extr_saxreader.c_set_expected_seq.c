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
struct call_entry {int dummy; } ;

/* Variables and functions */
 struct call_entry* expectCall ; 

__attribute__((used)) static void set_expected_seq(struct call_entry *expected)
{
    expectCall = expected;
}