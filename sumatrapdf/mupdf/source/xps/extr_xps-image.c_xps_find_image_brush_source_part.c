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
typedef  int /*<<< orphan*/  xps_part ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_xml ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* fz_xml_att (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/ * xps_read_part (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xps_resolve_url (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,char*,int) ; 

__attribute__((used)) static void
xps_find_image_brush_source_part(fz_context *ctx, xps_document *doc, char *base_uri, fz_xml *root, xps_part **image_part, xps_part **profile_part)
{
	char *image_source_att;
	char buf[1024];
	char partname[1024];
	char *image_name;
	char *profile_name;
	char *p;

	image_source_att = fz_xml_att(root, "ImageSource");
	if (!image_source_att)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find image source attribute");

	/* "{ColorConvertedBitmap /Resources/Image.tiff /Resources/Profile.icc}" */
	if (strstr(image_source_att, "{ColorConvertedBitmap") == image_source_att)
	{
		image_name = NULL;
		profile_name = NULL;

		fz_strlcpy(buf, image_source_att, sizeof buf);
		p = strchr(buf, ' ');
		if (p)
		{
			image_name = p + 1;
			p = strchr(p + 1, ' ');
			if (p)
			{
				*p = 0;
				profile_name = p + 1;
				p = strchr(p + 1, '}');
				if (p)
					*p = 0;
			}
		}
	}
	else
	{
		image_name = image_source_att;
		profile_name = NULL;
	}

	if (!image_name)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot find image source");

	if (image_part)
	{
		xps_resolve_url(ctx, doc, partname, base_uri, image_name, sizeof partname);
		*image_part = xps_read_part(ctx, doc, partname);
	}

	if (profile_part)
	{
		if (profile_name)
		{
			xps_resolve_url(ctx, doc, partname, base_uri, profile_name, sizeof partname);
			*profile_part = xps_read_part(ctx, doc, partname);
		}
		else
			*profile_part = NULL;
	}
}