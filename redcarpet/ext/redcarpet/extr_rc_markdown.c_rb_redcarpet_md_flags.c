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
typedef  int /*<<< orphan*/  VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  CSTR2SYM (char*) ; 
 int /*<<< orphan*/  Check_Type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int MKDEXT_AUTOLINK ; 
 unsigned int MKDEXT_DISABLE_INDENTED_CODE ; 
 unsigned int MKDEXT_FENCED_CODE ; 
 unsigned int MKDEXT_FOOTNOTES ; 
 unsigned int MKDEXT_HIGHLIGHT ; 
 unsigned int MKDEXT_LAX_SPACING ; 
 unsigned int MKDEXT_NO_INTRA_EMPHASIS ; 
 unsigned int MKDEXT_QUOTE ; 
 unsigned int MKDEXT_SPACE_HEADERS ; 
 unsigned int MKDEXT_STRIKETHROUGH ; 
 unsigned int MKDEXT_SUPERSCRIPT ; 
 unsigned int MKDEXT_TABLES ; 
 unsigned int MKDEXT_UNDERLINE ; 
 scalar_t__ Qtrue ; 
 int /*<<< orphan*/  T_HASH ; 
 scalar_t__ rb_hash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb_redcarpet_md_flags(VALUE hash, unsigned int *enabled_extensions_p)
{
	unsigned int extensions = 0;

	Check_Type(hash, T_HASH);

	/**
	 * Markdown extensions -- all disabled by default
	 */
	if (rb_hash_lookup(hash, CSTR2SYM("no_intra_emphasis")) == Qtrue)
		extensions |= MKDEXT_NO_INTRA_EMPHASIS;

	if (rb_hash_lookup(hash, CSTR2SYM("tables")) == Qtrue)
		extensions |= MKDEXT_TABLES;

	if (rb_hash_lookup(hash, CSTR2SYM("fenced_code_blocks")) == Qtrue)
		extensions |= MKDEXT_FENCED_CODE;

	if (rb_hash_lookup(hash, CSTR2SYM("disable_indented_code_blocks")) == Qtrue)
		extensions |= MKDEXT_DISABLE_INDENTED_CODE;

	if (rb_hash_lookup(hash, CSTR2SYM("autolink")) == Qtrue)
		extensions |= MKDEXT_AUTOLINK;

	if (rb_hash_lookup(hash, CSTR2SYM("strikethrough")) == Qtrue)
		extensions |= MKDEXT_STRIKETHROUGH;

	if (rb_hash_lookup(hash, CSTR2SYM("underline")) == Qtrue)
		extensions |= MKDEXT_UNDERLINE;

	if (rb_hash_lookup(hash, CSTR2SYM("highlight")) == Qtrue)
		extensions |= MKDEXT_HIGHLIGHT;

	if (rb_hash_lookup(hash, CSTR2SYM("quote")) == Qtrue)
		extensions |= MKDEXT_QUOTE;

	if (rb_hash_lookup(hash, CSTR2SYM("lax_spacing")) == Qtrue)
		extensions |= MKDEXT_LAX_SPACING;

	if (rb_hash_lookup(hash, CSTR2SYM("space_after_headers")) == Qtrue)
		extensions |= MKDEXT_SPACE_HEADERS;

	if (rb_hash_lookup(hash, CSTR2SYM("superscript")) == Qtrue)
		extensions |= MKDEXT_SUPERSCRIPT;

	if (rb_hash_lookup(hash, CSTR2SYM("footnotes")) == Qtrue)
		extensions |= MKDEXT_FOOTNOTES;

	*enabled_extensions_p = extensions;
}