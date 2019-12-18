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
struct info {int dummy; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*,char*) ; 
 unsigned char const* gif_read_icc (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*) ; 
 unsigned char const* gif_read_subblocks (int /*<<< orphan*/ *,struct info*,unsigned char const*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int memcmp (unsigned char const*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,unsigned char const*,int) ; 
 scalar_t__ nelem (char**) ; 

__attribute__((used)) static const unsigned char *
gif_read_ae(fz_context *ctx, struct info *info, const unsigned char *p, const unsigned char *end)
{
	static char *ignorable[] = {
		"NETSACPE2.0", "ANIMEXTS1.0", "XMP DataXMP",
		"ZGATEXTI5\0\0", "ZGATILEI5\0\0", "ZGANPIMGI5\0", "ZGACTRLI5\0\0",
		"ZGAVECTI5\0\0", "ZGAALPHAI5\0", "ZGATITLE4.0", "ZGATEXTI4.0",
	};
	int i, ignored;

	if (end - p < 14)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end in application extension in gif image");
	if (p[2] != 0x0b)
		fz_throw(ctx, FZ_ERROR_GENERIC, "out of range application extension block size in gif image");

	ignored = 0;
	for (i = 0; i < (int)nelem(ignorable); i++)
		ignored |= memcmp(&p[3], ignorable[i], 8 + 3);
	if (!ignored)
	{
		char extension[9];
		memmove(extension, &p[3], 8);
		extension[8] = '\0';
		fz_warn(ctx, "ignoring unsupported application extension '%s' in gif image", extension);
	}

	if (!memcmp(&p[3], "ICCRGBG1012", 11))
		return gif_read_icc(ctx, info, p + 14, end);

	return gif_read_subblocks(ctx, info, p + 14, end, NULL);
}