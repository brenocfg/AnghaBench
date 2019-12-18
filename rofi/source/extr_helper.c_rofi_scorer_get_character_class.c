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
typedef  int /*<<< orphan*/  gunichar ;
typedef  enum CharClass { ____Placeholder_CharClass } CharClass ;

/* Variables and functions */
 int DIGIT ; 
 int LOWER ; 
 int NON_WORD ; 
 int UPPER ; 
 scalar_t__ g_unichar_isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ g_unichar_islower (int /*<<< orphan*/ ) ; 
 scalar_t__ g_unichar_isupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum CharClass rofi_scorer_get_character_class ( gunichar c )
{
    if ( g_unichar_islower ( c ) ) {
        return LOWER;
    }
    if ( g_unichar_isupper ( c ) ) {
        return UPPER;
    }
    if ( g_unichar_isdigit ( c ) ) {
        return DIGIT;
    }
    return NON_WORD;
}