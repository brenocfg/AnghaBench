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
 int /*<<< orphan*/  assert (int) ; 
 int us_atof (char const*) ; 
 int us_strtod (char const*,char**) ; 

int main (void)
{
    const char dot9[] = "999999.999999";
    const char comma9[] = "999999,999999";
    const char sharp9[] = "999999#999999";
    char *end;

    assert (us_atof("0") == 0.);
    assert (us_atof("1") == 1.);
    assert (us_atof("1.") == 1.);
    assert (us_atof("1,") == 1.);
    assert (us_atof("1#") == 1.);
    assert (us_atof(dot9) == 999999.999999);
    assert (us_atof(comma9) == 999999.);
    assert (us_atof(sharp9) == 999999.);
    assert (us_atof("invalid") == 0.);

    assert ((us_strtod(dot9, &end ) == 999999.999999)
            && (*end == '\0'));
    assert ((us_strtod(comma9, &end ) == 999999.)
            && (*end == ','));
    assert ((us_strtod(sharp9, &end ) == 999999.)
            && (*end == '#'));

    return 0;
}