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
typedef  int /*<<< orphan*/  IHTMLOptionElement ;

/* Variables and functions */
 int VARIANT_FALSE ; 
 int VARIANT_TRUE ; 
 int /*<<< orphan*/  test_option_defaultSelected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_option_put_defaultSelected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_option_put_selected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_option_selected (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_option_defaultSelected_property(IHTMLOptionElement *option)
{
    test_option_defaultSelected(option, VARIANT_FALSE);
    test_option_selected(option, VARIANT_FALSE);

    test_option_put_defaultSelected(option, 0x100); /* Invalid value */
    test_option_defaultSelected(option, VARIANT_FALSE);
    test_option_selected(option, VARIANT_FALSE);

    test_option_put_defaultSelected(option, VARIANT_TRUE);
    test_option_defaultSelected(option, VARIANT_TRUE);
    test_option_selected(option, VARIANT_FALSE);

    test_option_put_defaultSelected(option, 0x100); /* Invalid value */
    test_option_defaultSelected(option, VARIANT_FALSE);
    test_option_selected(option, VARIANT_FALSE);

    test_option_put_selected(option, VARIANT_TRUE);
    test_option_selected(option, VARIANT_TRUE);
    test_option_defaultSelected(option, VARIANT_FALSE);

    test_option_put_defaultSelected(option, VARIANT_TRUE);
    test_option_defaultSelected(option, VARIANT_TRUE);
    test_option_selected(option, VARIANT_TRUE);

    /* Restore defaultSelected */
    test_option_put_defaultSelected(option, VARIANT_TRUE);
    test_option_put_selected(option, VARIANT_FALSE);
}