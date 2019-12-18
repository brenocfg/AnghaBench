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

/* Variables and functions */
 char const* fz_cleanname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  fz_urldecode (char*) ; 
 char* rel_path_from_idref (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const char *
path_from_idref(char *path, fz_xml *manifest, const char *base_uri, const char *idref, int n)
{
	const char *rel_path = rel_path_from_idref(manifest, idref);
	if (!rel_path)
	{
		path[0] = 0;
		return NULL;
	}
	fz_strlcpy(path, base_uri, n);
	fz_strlcat(path, "/", n);
	fz_strlcat(path, rel_path, n);
	return fz_cleanname(fz_urldecode(path));
}