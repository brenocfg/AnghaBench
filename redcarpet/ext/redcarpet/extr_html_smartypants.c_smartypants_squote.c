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
typedef  char uint8_t ;
struct smartypants_data {int /*<<< orphan*/  in_squote; int /*<<< orphan*/  in_dquote; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFPUTSL (struct buf*,char*) ; 
 int /*<<< orphan*/  bufput (struct buf*,char const*,size_t) ; 
 scalar_t__ smartypants_quotes (struct buf*,char,char const,char,int /*<<< orphan*/ *) ; 
 int squote_len (char const*,size_t) ; 
 char tolower (char const) ; 
 scalar_t__ word_boundary (char const) ; 

__attribute__((used)) static size_t
smartypants_squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size,
				   const uint8_t *squote_text, size_t squote_size)
{
	if (size >= 2) {
		uint8_t t1 = tolower(text[1]);
		int next_squote_len = squote_len(text+1, size-1);

		// convert '' to &ldquo; or &rdquo;
		if (next_squote_len > 0) {
			uint8_t next_char = (size > 1+next_squote_len) ? text[1+next_squote_len] : 0;
			if (smartypants_quotes(ob, previous_char, next_char, 'd', &smrt->in_dquote))
				return next_squote_len;
		}

		if (smartypants_quotes(ob, previous_char, size > 0 ? text[1] : 0, 's', &smrt->in_squote))
			return 0;

		// trailing single quotes: students', tryin'
		if (word_boundary(t1)) {
			BUFPUTSL(ob, "&rsquo;");
			return 0;
		}

		// Tom's, isn't, I'm, I'd
		if ((t1 == 's' || t1 == 't' || t1 == 'm' || t1 == 'd') &&
			(size == 3 || word_boundary(text[2]))) {
			BUFPUTSL(ob, "&rsquo;");
			return 0;
		}

		// you're, you'll, you've
		if (size >= 3) {
			uint8_t t2 = tolower(text[2]);

			if (((t1 == 'r' && t2 == 'e') ||
				(t1 == 'l' && t2 == 'l') ||
				(t1 == 'v' && t2 == 'e')) &&
				(size == 4 || word_boundary(text[3]))) {
				BUFPUTSL(ob, "&rsquo;");
				return 0;
			}
		}
	}

	bufput(ob, squote_text, squote_size);
	return 0;
}