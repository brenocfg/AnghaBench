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
struct box {char* text; } ;

/* Variables and functions */
 char* box_text_offset (struct box*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void
box_text_copy(struct box *box, size_t cells, const char *src, size_t srclen)
{
	char *dst = box_text_offset(box, cells);

	box->text = dst;
	strncpy(dst, src, srclen);
}