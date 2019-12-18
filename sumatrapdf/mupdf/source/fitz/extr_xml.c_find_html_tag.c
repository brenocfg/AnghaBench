#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* tag; } ;

/* Variables and functions */
 int fz_xml_html_tag__NONE ; 
 TYPE_1__* html_tags ; 
 int nelem (TYPE_1__*) ; 
 int strncmp (int*,char const*,int) ; 

__attribute__((used)) static int
find_html_tag(const char *tag, int len)
{
	int low = 0;
	int high = nelem(html_tags);
	int mid;

	while (low != high)
	{
		int cmp;
		mid = (low + high)>>1;
		cmp = strncmp(html_tags[mid].tag, tag, len);
		if (cmp == 0)
			cmp = html_tags[mid].tag[len];
		if (cmp == 0)
			return mid;
		if (cmp < 0)
			low = mid+1;
		else
			high = mid;
	}

	return fz_xml_html_tag__NONE;
}