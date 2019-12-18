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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  expect_LayerValue_imp (int /*<<< orphan*/ ,char const*,char const*) ; 

__attribute__((used)) static void expect_LayerValue_imp2(BOOL bMachine, const char* valueName, const char* value, int use_alt, const char* alt_value)
{
    expect_LayerValue_imp(bMachine, valueName, use_alt ? alt_value : value);
}