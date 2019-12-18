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
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
xps_rels_for_part(fz_context *ctx, xps_document *doc, char *buf, char *name, int buflen)
{
	char *p, *basename;
	p = strrchr(name, '/');
	basename = p ? p + 1 : name;
	fz_strlcpy(buf, name, buflen);
	p = strrchr(buf, '/');
	if (p) *p = 0;
	fz_strlcat(buf, "/_rels/", buflen);
	fz_strlcat(buf, basename, buflen);
	fz_strlcat(buf, ".rels", buflen);
}