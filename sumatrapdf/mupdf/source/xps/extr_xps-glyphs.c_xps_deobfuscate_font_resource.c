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
struct TYPE_3__ {char* name; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ xps_part ;
typedef  int /*<<< orphan*/  xps_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 size_t fz_buffer_storage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ishex (char) ; 
 char* strrchr (char*,char) ; 
 int unhex (unsigned char) ; 

__attribute__((used)) static void
xps_deobfuscate_font_resource(fz_context *ctx, xps_document *doc, xps_part *part)
{
	unsigned char buf[33];
	unsigned char key[16];
	unsigned char *data;
	size_t size;
	char *p;
	int i;

	size = fz_buffer_storage(ctx, part->data, &data);
	if (size < 32)
	{
		fz_warn(ctx, "insufficient data for font deobfuscation");
		return;
	}

	p = strrchr(part->name, '/');
	if (!p)
		p = part->name;

	for (i = 0; i < 32 && *p; p++)
	{
		if (ishex(*p))
			buf[i++] = *p;
	}
	buf[i] = 0;

	if (i != 32)
	{
		fz_warn(ctx, "cannot extract GUID from obfuscated font part name");
		return;
	}

	for (i = 0; i < 16; i++)
		key[i] = unhex(buf[i*2+0]) * 16 + unhex(buf[i*2+1]);

	for (i = 0; i < 16; i++)
	{
		data[i] ^= key[15-i];
		data[i+16] ^= key[15-i];
	}
}