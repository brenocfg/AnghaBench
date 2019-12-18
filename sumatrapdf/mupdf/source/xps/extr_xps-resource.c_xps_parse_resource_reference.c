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
typedef  int /*<<< orphan*/  xps_resource ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/ * xps_lookup_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**) ; 

__attribute__((used)) static fz_xml *
xps_parse_resource_reference(fz_context *ctx, xps_document *doc, xps_resource *dict, char *att, char **urip)
{
	char name[1024];
	char *s;

	if (strstr(att, "{StaticResource ") != att)
		return NULL;

	fz_strlcpy(name, att + 16, sizeof name);
	s = strrchr(name, '}');
	if (s)
		*s = 0;

	return xps_lookup_resource(ctx, doc, dict, name, urip);
}