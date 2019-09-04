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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  IHTMLOptionElement_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARIANT_FALSE ; 
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/ * create_option_elem (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  test_option_defaultSelected_property (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_option_get_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_option_put_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_option_put_text (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_option_put_value (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_create_option_elem(IHTMLDocument2 *doc)
{
    IHTMLOptionElement *option;

    option = create_option_elem(doc, "test text", "test value");

    test_option_put_text(option, "new text");
    test_option_put_value(option, "new value");
    test_option_get_index(option, 0);
    test_option_defaultSelected_property(option);
    test_option_put_selected(option, VARIANT_TRUE);
    test_option_put_selected(option, VARIANT_FALSE);

    IHTMLOptionElement_Release(option);
}