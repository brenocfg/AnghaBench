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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char locale_decimal_point ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void fpconv_update_locale()
{
    char buf[8];

    snprintf(buf, sizeof(buf), "%g", 0.5);

    /* Failing this test might imply the platform has a buggy dtoa
     * implementation or wide characters */
    if (buf[0] != '0' || buf[2] != '5' || buf[3] != 0) {
        fprintf(stderr, "Error: wide characters found or printf() bug.");
        abort();
    }

    locale_decimal_point = buf[1];
}