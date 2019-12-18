#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ XrmOption ;

/* Variables and functions */
 int /*<<< orphan*/  print_option_boolean (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_option_char (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_option_number (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_option_snumber (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_option_string (TYPE_1__*,int) ; 
#define  xrm_Boolean 132 
#define  xrm_Char 131 
#define  xrm_Number 130 
#define  xrm_SNumber 129 
#define  xrm_String 128 

__attribute__((used)) static void print_option ( XrmOption *xo, int is_term )
{
    switch ( xo->type )
    {
    case xrm_String:
        print_option_string ( xo, is_term );
        break;
    case xrm_Number:
        print_option_number ( xo, is_term );
        break;
    case xrm_SNumber:
        print_option_snumber ( xo, is_term );
        break;
    case xrm_Boolean:
        print_option_boolean ( xo, is_term );
        break;
    case xrm_Char:
        print_option_char ( xo, is_term );
        break;
    default:
        break;
    }
}