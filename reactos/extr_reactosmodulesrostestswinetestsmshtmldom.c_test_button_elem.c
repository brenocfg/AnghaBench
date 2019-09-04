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
typedef  int /*<<< orphan*/  IHTMLElement ;

/* Variables and functions */
 int /*<<< orphan*/  VARIANT_TRUE ; 
 int /*<<< orphan*/  set_button_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_button_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_elem_istextedit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_button_elem(IHTMLElement *elem)
{
    test_button_name(elem, NULL);
    set_button_name(elem, "button name");

    test_elem_istextedit(elem, VARIANT_TRUE);
}