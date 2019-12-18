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
struct stat_array {int dummy; } ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_5__ {int cb_namewidth; scalar_t__ cb_scripted; int /*<<< orphan*/  cb_flags; scalar_t__ cb_literal; } ;
typedef  TYPE_1__ iostat_cbdata_t ;
typedef  enum iostat_type { ____Placeholder_iostat_type } iostat_type ;

/* Variables and functions */
 size_t IOS_HISTO_IDX (int /*<<< orphan*/ ) ; 
 unsigned int MAX (int,unsigned int) ; 
 struct stat_array* calc_and_alloc_stats_ex (char const**,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_calc_stats (struct stat_array*,unsigned int) ; 
 int /*<<< orphan*/ * histo_to_title ; 
 int /*<<< orphan*/ * iostat_bottom_labels ; 
 unsigned int label_array_len (int /*<<< orphan*/ ) ; 
 scalar_t__ log10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_iostat_header_impl (TYPE_1__*,unsigned int,char const*) ; 
 int /*<<< orphan*/  print_iostat_histo (struct stat_array*,unsigned int,TYPE_1__*,unsigned int,unsigned int,double) ; 
 int /*<<< orphan*/  print_solid_separator (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stat_histo_max (struct stat_array*,unsigned int) ; 
 unsigned int str_array_len (char const**) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 char*** vsx_type_to_nvlist ; 

__attribute__((used)) static void
print_iostat_histos(iostat_cbdata_t *cb, nvlist_t *oldnv,
    nvlist_t *newnv, double scale, const char *name)
{
	unsigned int column_width;
	unsigned int namewidth;
	unsigned int entire_width;
	enum iostat_type type;
	struct stat_array *nva;
	const char **names;
	unsigned int names_len;

	/* What type of histo are we? */
	type = IOS_HISTO_IDX(cb->cb_flags);

	/* Get NULL-terminated array of nvlist names for our histo */
	names = vsx_type_to_nvlist[type];
	names_len = str_array_len(names); /* num of names */

	nva = calc_and_alloc_stats_ex(names, names_len, oldnv, newnv);

	if (cb->cb_literal) {
		column_width = MAX(5,
		    (unsigned int) log10(stat_histo_max(nva, names_len)) + 1);
	} else {
		column_width = 5;
	}

	namewidth = MAX(cb->cb_namewidth,
	    strlen(histo_to_title[IOS_HISTO_IDX(cb->cb_flags)]));

	/*
	 * Calculate the entire line width of what we're printing.  The
	 * +2 is for the two spaces between columns:
	 */
	/*	 read  write				*/
	/*	-----  -----				*/
	/*	|___|  <---------- column_width		*/
	/*						*/
	/*	|__________|  <--- entire_width		*/
	/*						*/
	entire_width = namewidth + (column_width + 2) *
	    label_array_len(iostat_bottom_labels[type]);

	if (cb->cb_scripted)
		printf("%s\n", name);
	else
		print_iostat_header_impl(cb, column_width, name);

	print_iostat_histo(nva, names_len, cb, column_width,
	    namewidth, scale);

	free_calc_stats(nva, names_len);
	if (!cb->cb_scripted)
		print_solid_separator(entire_width);
}