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
typedef  int uint32_t ;
typedef  int fz_bidi_flags ;
typedef  scalar_t__ fz_bidi_chartype ;

/* Variables and functions */
 int FZ_BIDI_CLASSIFY_WHITE_SPACE ; 
 int* char_from_types ; 
 scalar_t__ class_from_ch_n (int const) ; 
 scalar_t__ class_from_ch_ws (int const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
classify_characters(const uint32_t *text,
		fz_bidi_chartype *types,
		size_t len,
		fz_bidi_flags flags)
{
	size_t i;

	if ((flags & FZ_BIDI_CLASSIFY_WHITE_SPACE)!=0)
	{
		for (i = 0; i < len; i++)
		{
			types[i] = class_from_ch_ws(text[i]);
		}
	}
	else
	{
#ifdef DEBUG_BIDI_VERBOSE
		fprintf(stderr, "Text:  ");
		for (i = 0; i < len; i++)
		{
			/* So that we can actually sort of read the debug string, any
			 * non-ascii characters are replaced with a 1-digit hash
			 * value from 0-9, making non-english characters appear
			 * as numbers
			 */
			fprintf(stderr, "%c", (text[i] <= 127 && text[i] >= 32) ?
					text[i] : text[i] % 9 + '0');
		}
		fprintf(stderr, "\nTypes: ");
#endif
		for (i = 0; i < len; i++)
		{
			types[i] = class_from_ch_n(text[i]);
#ifdef DEBUG_BIDI_VERBOSE
			fprintf(stderr, "%c", char_from_types[(int)types[i]]);
#endif
		}
#ifdef DEBUG_BIDI_VERBOSE
		fprintf(stderr, "\n");
#endif
	}
}