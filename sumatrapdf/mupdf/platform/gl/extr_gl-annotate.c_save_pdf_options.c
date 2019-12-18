#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t do_encrypt; char** upwd_utf8; char** opwd_utf8; scalar_t__ do_sanitize; scalar_t__ do_clean; scalar_t__ do_garbage; scalar_t__ do_linear; scalar_t__ do_incremental; scalar_t__ do_compress_fonts; scalar_t__ do_compress_images; scalar_t__ do_compress; scalar_t__ do_decompress; scalar_t__ do_ascii; scalar_t__ do_pretty; } ;
struct TYPE_5__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  NW ; 
 size_t PDF_ENCRYPT_KEEP ; 
 int PDF_ENCRYPT_RC4_40 ; 
 int /*<<< orphan*/  T ; 
 scalar_t__ UI_INPUT_EDIT ; 
 int /*<<< orphan*/  X ; 
 char** cryptalgo_names ; 
 int /*<<< orphan*/  fz_strlcpy (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelem (char**) ; 
 TYPE_1__ opwinput ; 
 TYPE_3__ save_opts ; 
 int /*<<< orphan*/  ui_checkbox (char*,scalar_t__*) ; 
 scalar_t__ ui_input (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ui_label (char*) ; 
 int /*<<< orphan*/  ui_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ui_select (char*,char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_spacer () ; 
 TYPE_1__ upwinput ; 

__attribute__((used)) static void save_pdf_options(void)
{
	const char *cryptalgo = cryptalgo_names[save_opts.do_encrypt];
	int choice;

	ui_layout(T, X, NW, 2, 2);
	ui_label("PDF write options:");
	ui_layout(T, X, NW, 4, 2);

	ui_checkbox("Incremental", &save_opts.do_incremental);
	ui_spacer();
	ui_checkbox("Pretty-print", &save_opts.do_pretty);
	ui_checkbox("Ascii", &save_opts.do_ascii);
	ui_checkbox("Decompress", &save_opts.do_decompress);
	ui_checkbox("Compress", &save_opts.do_compress);
	ui_checkbox("Compress images", &save_opts.do_compress_images);
	ui_checkbox("Compress fonts", &save_opts.do_compress_fonts);
	if (save_opts.do_incremental)
	{
		save_opts.do_garbage = 0;
		save_opts.do_linear = 0;
		save_opts.do_clean = 0;
		save_opts.do_sanitize = 0;
		save_opts.do_encrypt = PDF_ENCRYPT_KEEP;
	}
	else
	{
		ui_spacer();
		ui_checkbox("Linearize", &save_opts.do_linear);
		ui_checkbox("Garbage collect", &save_opts.do_garbage);
		ui_checkbox("Clean syntax", &save_opts.do_clean);
		ui_checkbox("Sanitize syntax", &save_opts.do_sanitize);

		ui_spacer();
		ui_label("Encryption:");
		choice = ui_select("Encryption", cryptalgo, cryptalgo_names, nelem(cryptalgo_names));
		if (choice != -1)
			save_opts.do_encrypt = choice;
	}

	if (save_opts.do_encrypt >= PDF_ENCRYPT_RC4_40)
	{
		ui_spacer();
		ui_label("User password:");
		if (ui_input(&upwinput, 32, 1) >= UI_INPUT_EDIT)
			fz_strlcpy(save_opts.upwd_utf8, upwinput.text, nelem(save_opts.upwd_utf8));
		ui_label("Owner password:");
		if (ui_input(&opwinput, 32, 1) >= UI_INPUT_EDIT)
			fz_strlcpy(save_opts.opwd_utf8, opwinput.text, nelem(save_opts.opwd_utf8));
	}
}