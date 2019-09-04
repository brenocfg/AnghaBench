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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  le16_t ;

/* Variables and functions */
 int /*<<< orphan*/  read16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_utf16(wchar_t *name, unsigned char *entry)
{
    int i;
    for (i=0; i<5; i++)
	name[i] = read16((le16_t*)&entry[1 + 2*i]);
    for (i=5; i<11; i++)
	name[i] = read16((le16_t*)&entry[4 + 2*i]);
    for (i=11; i<12; i++)
	name[i] = read16((le16_t*)&entry[6 + 2*i]);
}