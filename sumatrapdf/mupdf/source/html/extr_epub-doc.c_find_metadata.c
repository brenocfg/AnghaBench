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
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 char* fz_strdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_xml_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_xml_find_down (int /*<<< orphan*/ *,char*) ; 
 char* fz_xml_text (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
find_metadata(fz_context *ctx, fz_xml *metadata, char *key)
{
	char *text = fz_xml_text(fz_xml_down(fz_xml_find_down(metadata, key)));
	if (text)
		return fz_strdup(ctx, text);
	return NULL;
}