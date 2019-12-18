#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ link; scalar_t__ image; scalar_t__ linebreak; scalar_t__ codespan; scalar_t__ triple_emphasis; scalar_t__ double_emphasis; scalar_t__ emphasis; } ;
struct sd_markdown {unsigned int ext_flags; size_t max_nesting; scalar_t__ in_link_body; void* opaque; void** active_char; TYPE_1__ cb; int /*<<< orphan*/ * work_bufs; } ;
struct sd_callbacks {int dummy; } ;

/* Variables and functions */
 size_t BUFFER_BLOCK ; 
 size_t BUFFER_SPAN ; 
 void* MD_CHAR_AUTOLINK_EMAIL ; 
 void* MD_CHAR_AUTOLINK_URL ; 
 void* MD_CHAR_AUTOLINK_WWW ; 
 void* MD_CHAR_CODESPAN ; 
 void* MD_CHAR_EMPHASIS ; 
 void* MD_CHAR_ENTITITY ; 
 void* MD_CHAR_ESCAPE ; 
 void* MD_CHAR_LANGLE ; 
 void* MD_CHAR_LINEBREAK ; 
 void* MD_CHAR_LINK ; 
 void* MD_CHAR_QUOTE ; 
 void* MD_CHAR_SUPERSCRIPT ; 
 unsigned int MKDEXT_AUTOLINK ; 
 unsigned int MKDEXT_HIGHLIGHT ; 
 unsigned int MKDEXT_QUOTE ; 
 unsigned int MKDEXT_STRIKETHROUGH ; 
 unsigned int MKDEXT_SUPERSCRIPT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct sd_markdown* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct sd_callbacks const*,int) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 int /*<<< orphan*/  redcarpet_stack_init (int /*<<< orphan*/ *,int) ; 

struct sd_markdown *
sd_markdown_new(
	unsigned int extensions,
	size_t max_nesting,
	const struct sd_callbacks *callbacks,
	void *opaque)
{
	struct sd_markdown *md = NULL;

	assert(max_nesting > 0 && callbacks);

	md = malloc(sizeof(struct sd_markdown));
	if (!md)
		return NULL;

	memcpy(&md->cb, callbacks, sizeof(struct sd_callbacks));

	redcarpet_stack_init(&md->work_bufs[BUFFER_BLOCK], 4);
	redcarpet_stack_init(&md->work_bufs[BUFFER_SPAN], 8);

	memset(md->active_char, 0x0, 256);

	if (md->cb.emphasis || md->cb.double_emphasis || md->cb.triple_emphasis) {
		md->active_char['*'] = MD_CHAR_EMPHASIS;
		md->active_char['_'] = MD_CHAR_EMPHASIS;

		if (extensions & MKDEXT_STRIKETHROUGH)
			md->active_char['~'] = MD_CHAR_EMPHASIS;
		if (extensions & MKDEXT_HIGHLIGHT)
			md->active_char['='] = MD_CHAR_EMPHASIS;
		if (extensions & MKDEXT_QUOTE)
			md->active_char['"'] = MD_CHAR_QUOTE;
	}

	if (md->cb.codespan)
		md->active_char['`'] = MD_CHAR_CODESPAN;

	if (md->cb.linebreak)
		md->active_char['\n'] = MD_CHAR_LINEBREAK;

	if (md->cb.image || md->cb.link)
		md->active_char['['] = MD_CHAR_LINK;

	md->active_char['<'] = MD_CHAR_LANGLE;
	md->active_char['\\'] = MD_CHAR_ESCAPE;
	md->active_char['&'] = MD_CHAR_ENTITITY;

	if (extensions & MKDEXT_AUTOLINK) {
		md->active_char[':'] = MD_CHAR_AUTOLINK_URL;
		md->active_char['@'] = MD_CHAR_AUTOLINK_EMAIL;
		md->active_char['w'] = MD_CHAR_AUTOLINK_WWW;
	}

	if (extensions & MKDEXT_SUPERSCRIPT)
		md->active_char['^'] = MD_CHAR_SUPERSCRIPT;

	/* Extension data */
	md->ext_flags = extensions;
	md->opaque = opaque;
	md->max_nesting = max_nesting;
	md->in_link_body = 0;

	return md;
}