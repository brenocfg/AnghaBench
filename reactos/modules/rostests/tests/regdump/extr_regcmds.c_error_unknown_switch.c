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
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  printf (char*,char) ; 

void error_unknown_switch(char chu, char *s)
{
    if (isalpha(chu)) {
        printf("Undefined switch /%c!\n", chu);
    } else {
        printf("Alphabetic character is expected after '%c' "
               "in switch specification\n", *(s - 1));
    }
    //exit(1);
}