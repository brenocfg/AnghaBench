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
 int CS_DBLCLKS ; 
 int CS_DROPSHADOW ; 
 int CS_GLOBALCLASS ; 
 int CS_HREDRAW ; 
 int CS_PARENTDC ; 
 int CS_SAVEBITS ; 
 int CS_VREDRAW ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  check_class (char*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_builtin_classes(void)
{
    /* check style bits */
    check_class( "Button",     1, CS_PARENTDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS, 0, FALSE );
    check_class( "ComboBox",   1, CS_PARENTDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS, 0, FALSE );
    check_class( "Edit",       1, CS_PARENTDC | CS_DBLCLKS | CS_GLOBALCLASS, 0, FALSE );
    check_class( "ListBox",    1, CS_PARENTDC | CS_DBLCLKS | CS_GLOBALCLASS, 0, FALSE );
    check_class( "ScrollBar",  1, CS_PARENTDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS, 0, FALSE );
    check_class( "Static",     1, CS_PARENTDC | CS_DBLCLKS | CS_GLOBALCLASS, 0, FALSE );
    check_class( "ComboLBox",  1, CS_SAVEBITS | CS_DBLCLKS | CS_DROPSHADOW | CS_GLOBALCLASS, CS_DROPSHADOW, FALSE );
}