#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int do_garbage; int do_appearance; void* permissions; int /*<<< orphan*/  upwd_utf8; int /*<<< orphan*/  opwd_utf8; void* do_encrypt; void* do_incremental; void* do_sanitize; void* do_clean; void* do_linear; void* do_pretty; void* do_ascii; void* do_compress_images; void* do_compress_fonts; void* do_compress; void* do_decompress; } ;
typedef  TYPE_1__ pdf_write_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 void* PDF_ENCRYPT_AES_128 ; 
 void* PDF_ENCRYPT_AES_256 ; 
 void* PDF_ENCRYPT_KEEP ; 
 void* PDF_ENCRYPT_NONE ; 
 void* PDF_ENCRYPT_RC4_128 ; 
 void* PDF_ENCRYPT_RC4_40 ; 
 void* PDF_ENCRYPT_UNKNOWN ; 
 void* fz_atoi (char const*) ; 
 int /*<<< orphan*/  fz_copy_option (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fz_has_option (int /*<<< orphan*/ *,char const*,char*,char const**) ; 
 void* fz_option_eq (char const*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nelem (int /*<<< orphan*/ ) ; 

pdf_write_options *
pdf_parse_write_options(fz_context *ctx, pdf_write_options *opts, const char *args)
{
	const char *val;

	memset(opts, 0, sizeof *opts);

	if (fz_has_option(ctx, args, "decompress", &val))
		opts->do_decompress = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "compress", &val))
		opts->do_compress = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "compress-fonts", &val))
		opts->do_compress_fonts = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "compress-images", &val))
		opts->do_compress_images = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "ascii", &val))
		opts->do_ascii = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "pretty", &val))
		opts->do_pretty = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "linearize", &val))
		opts->do_linear = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "clean", &val))
		opts->do_clean = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "sanitize", &val))
		opts->do_sanitize = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "incremental", &val))
		opts->do_incremental = fz_option_eq(val, "yes");
	if (fz_has_option(ctx, args, "decrypt", &val))
		opts->do_encrypt = fz_option_eq(val, "yes") ? PDF_ENCRYPT_NONE : PDF_ENCRYPT_KEEP;
	if (fz_has_option(ctx, args, "encrypt", &val))
	{
		opts->do_encrypt = PDF_ENCRYPT_UNKNOWN;
		if (fz_option_eq(val, "none") || fz_option_eq(val, "no"))
			opts->do_encrypt = PDF_ENCRYPT_NONE;
		if (fz_option_eq(val, "keep"))
			opts->do_encrypt = PDF_ENCRYPT_KEEP;
		if (fz_option_eq(val, "rc4-40") || fz_option_eq(val, "yes"))
			opts->do_encrypt = PDF_ENCRYPT_RC4_40;
		if (fz_option_eq(val, "rc4-128"))
			opts->do_encrypt = PDF_ENCRYPT_RC4_128;
		if (fz_option_eq(val, "aes-128"))
			opts->do_encrypt = PDF_ENCRYPT_AES_128;
		if (fz_option_eq(val, "aes-256"))
			opts->do_encrypt = PDF_ENCRYPT_AES_256;
	}
	if (fz_has_option(ctx, args, "owner-password", &val))
		fz_copy_option(ctx, val, opts->opwd_utf8, nelem(opts->opwd_utf8));
	if (fz_has_option(ctx, args, "user-password", &val))
		fz_copy_option(ctx, val, opts->upwd_utf8, nelem(opts->upwd_utf8));
	if (fz_has_option(ctx, args, "permissions", &val))
		opts->permissions = fz_atoi(val);
	else
		opts->permissions = ~0;
	if (fz_has_option(ctx, args, "garbage", &val))
	{
		if (fz_option_eq(val, "yes"))
			opts->do_garbage = 1;
		else if (fz_option_eq(val, "compact"))
			opts->do_garbage = 2;
		else if (fz_option_eq(val, "deduplicate"))
			opts->do_garbage = 3;
		else
			opts->do_garbage = fz_atoi(val);
	}
	if (fz_has_option(ctx, args, "appearance", &val))
	{
		if (fz_option_eq(val, "yes"))
			opts->do_appearance = 1;
		else if (fz_option_eq(val, "all"))
			opts->do_appearance = 2;
	}

	return opts;
}