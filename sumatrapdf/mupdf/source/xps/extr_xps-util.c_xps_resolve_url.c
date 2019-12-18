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
 int /*<<< orphan*/  clean_path (char*) ; 
 int /*<<< orphan*/  fz_strlcat (char*,char*,int) ; 
 size_t fz_strlcpy (char*,char*,int) ; 
 char* skip_authority (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_scheme (char*) ; 

void
xps_resolve_url(fz_context *ctx, xps_document *doc, char *output, char *base_uri, char *path, int output_size)
{
	char *p = skip_authority(skip_scheme(path));

	if (p != path || path[0] == '/')
	{
		fz_strlcpy(output, path, output_size);
	}
	else
	{
		size_t len = fz_strlcpy(output, base_uri, output_size);
		if (len == 0 || output[len-1] != '/')
			fz_strlcat(output, "/", output_size);
		fz_strlcat(output, path, output_size);
	}
	clean_path(output);
}