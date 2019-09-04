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
typedef  char wchar_t ;

/* Variables and functions */

__attribute__((used)) static int wchar2digit(wchar_t c, int base) {
    if ((c>='0') && (c<='9') && (c<='0'+base-1)) return (c-'0');
    if (base<=10) return -1;
    if ((c>='A') && (c<='Z') && (c<='A'+base-11)) return (c-'A'+10);
    if ((c>='a') && (c<='z') && (c<='a'+base-11)) return (c-'a'+10);
    return -1;
}