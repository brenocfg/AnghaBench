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
 int /*<<< orphan*/  accept_punctuation_marks ; 
 int /*<<< orphan*/  error_exit (char*,char const*) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int toupper (int) ; 

__attribute__((used)) static int check_for_punctuation(int c, const char *name)
{
    c = toupper(c & 0xFF);
    if (!accept_punctuation_marks && !isalnum(c) && c != '_')
        error_exit("Punctuation mark in %s", name);
    return c;
}