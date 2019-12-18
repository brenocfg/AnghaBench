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
typedef  struct ref_format {char* member_0; char* member_1; } const ref_format ;
struct ref {size_t type; } ;

/* Variables and functions */
 size_t REFERENCE_BRANCH ; 
 size_t REFERENCE_REMOTE ; 
 size_t REFERENCE_TAG ; 
 scalar_t__ ref_is_remote (struct ref const*) ; 
 scalar_t__ ref_is_tag (struct ref const*) ; 

const struct ref_format *
get_ref_format(struct ref_format **ref_formats, const struct ref *ref)
{
	static const struct ref_format default_format = { "", "" };

	if (ref_formats) {
		struct ref_format *format = ref_formats[ref->type];

		if (!format && ref_is_tag(ref))
			format = ref_formats[REFERENCE_TAG];
		if (!format && ref_is_remote(ref))
			format = ref_formats[REFERENCE_REMOTE];
		if (!format)
			format = ref_formats[REFERENCE_BRANCH];
		if (format)
			return format;
	}

	return &default_format;
}