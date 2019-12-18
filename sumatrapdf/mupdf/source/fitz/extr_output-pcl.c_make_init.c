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
struct TYPE_3__ {int media_position; scalar_t__ media_position_set; scalar_t__ manual_feed; scalar_t__ manual_feed_set; } ;
typedef  TYPE_1__ fz_pcl_options ;
typedef  int /*<<< orphan*/  buf2 ;

/* Variables and functions */
 int /*<<< orphan*/  fz_snprintf (char*,int,char const*,int) ; 
 int /*<<< orphan*/  strncat (char*,char*,unsigned long) ; 

__attribute__((used)) static void
make_init(fz_pcl_options *pcl, char *buf, unsigned long len, const char *str, int res)
{
	int paper_source = -1;

	fz_snprintf(buf, len, str, res);

	if (pcl->manual_feed_set && pcl->manual_feed)
		paper_source = 2;
	else if (pcl->media_position_set && pcl->media_position >= 0)
		paper_source = pcl->media_position;
	if (paper_source >= 0)
	{
		char buf2[40];
		fz_snprintf(buf2, sizeof(buf2), "\033&l%dH", paper_source);
		strncat(buf, buf2, len);
	}
}