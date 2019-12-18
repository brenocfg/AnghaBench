#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unauthorized ;
typedef  int /*<<< orphan*/  grub_version_str ;
struct TYPE_2__ {char* grub2_version; } ;

/* Variables and functions */
 TYPE_1__ img_report ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  static_strcpy (char*,char*) ; 

void GetGrubVersion(char* buf, size_t buf_size)
{
	char *p, unauthorized[] = {'<', '>', ':', '|', '*', '?', '\\', '/'};
	size_t i;
	const char grub_version_str[] = "GRUB  version %s";

	for (i=0; i<buf_size; i++) {
		if (memcmp(&buf[i], grub_version_str, sizeof(grub_version_str)) == 0) {
			static_strcpy(img_report.grub2_version, &buf[i + sizeof(grub_version_str)]);
			break;
		}
	}
	// Sanitize the string
	for (p = &img_report.grub2_version[0]; *p; p++) {
		for (i=0; i<sizeof(unauthorized); i++) {
			if (*p == unauthorized[i])
				*p = '_';
		}
	}
	// <Shakes fist angrily> "KASPERSKYYYYYY!!!..." (https://github.com/pbatard/rufus/issues/467)
	// But seriously, these guys should know better than "security" through obscurity...
	if (img_report.grub2_version[0] == '0')
		img_report.grub2_version[0] = 0;
}