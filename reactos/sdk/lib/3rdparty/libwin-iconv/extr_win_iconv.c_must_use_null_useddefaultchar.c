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

__attribute__((used)) static int
must_use_null_useddefaultchar(int codepage)
{
    return (codepage == 65000 || codepage == 65001 ||
            codepage == 50220 || codepage == 50221 ||
            codepage == 50222 || codepage == 50225 ||
            codepage == 50227 || codepage == 50229 ||
            codepage == 52936 || codepage == 54936 ||
            (codepage >= 57002 && codepage <= 57011) ||
            codepage == 42);
}