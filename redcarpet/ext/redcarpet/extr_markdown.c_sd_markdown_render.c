#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* doc_footer ) (struct buf*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* doc_header ) (struct buf*,int /*<<< orphan*/ ) ;} ;
struct sd_markdown {int ext_flags; TYPE_2__* work_bufs; int /*<<< orphan*/  footnotes_used; int /*<<< orphan*/  footnotes_found; int /*<<< orphan*/  refs; int /*<<< orphan*/  opaque; TYPE_1__ cb; } ;
struct buf {int size; char* data; } ;
struct TYPE_4__ {scalar_t__ size; } ;

/* Variables and functions */
 size_t BUFFER_BLOCK ; 
 size_t BUFFER_SPAN ; 
 size_t MARKDOWN_GROW (int) ; 
 int MKDEXT_FENCED_CODE ; 
 int MKDEXT_FOOTNOTES ; 
 int REF_TABLE_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bufcstr (struct buf*) ; 
 int /*<<< orphan*/  bufgrow (struct buf*,size_t) ; 
 struct buf* bufnew (int) ; 
 int /*<<< orphan*/  bufputc (struct buf*,char) ; 
 int /*<<< orphan*/  bufrelease (struct buf*) ; 
 int /*<<< orphan*/  expand_tabs (struct buf*,char const*,size_t) ; 
 int /*<<< orphan*/  free_footnote_list (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_link_refs (int /*<<< orphan*/ ) ; 
 scalar_t__ is_codefence (char const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ is_footnote (char const*,size_t,size_t,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_ref (char const*,size_t,size_t,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  parse_block (struct buf*,struct sd_markdown*,char*,int) ; 
 int /*<<< orphan*/  parse_footnote_list (struct buf*,struct sd_markdown*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct buf*,int /*<<< orphan*/ ) ; 

void
sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md)
{
#define MARKDOWN_GROW(x) ((x) + ((x) >> 1))
	static const char UTF8_BOM[] = {0xEF, 0xBB, 0xBF};

	struct buf *text;
	size_t beg, end;
	int in_fence = 0;

	text = bufnew(64);
	if (!text)
		return;

	/* Preallocate enough space for our buffer to avoid expanding while copying */
	bufgrow(text, doc_size);

	/* reset the references table */
	memset(&md->refs, 0x0, REF_TABLE_SIZE * sizeof(void *));

	int footnotes_enabled  = md->ext_flags & MKDEXT_FOOTNOTES;
	int codefences_enabled = md->ext_flags & MKDEXT_FENCED_CODE;

	/* reset the footnotes lists */
	if (footnotes_enabled) {
		memset(&md->footnotes_found, 0x0, sizeof(md->footnotes_found));
		memset(&md->footnotes_used, 0x0, sizeof(md->footnotes_used));
	}

	/* first pass: looking for references, copying everything else */
	beg = 0;

	/* Skip a possible UTF-8 BOM, even though the Unicode standard
	 * discourages having these in UTF-8 documents */
	if (doc_size >= 3 && memcmp(document, UTF8_BOM, 3) == 0)
		beg += 3;

	while (beg < doc_size) { /* iterating over lines */
		if (codefences_enabled && (is_codefence(document + beg, doc_size - beg, NULL) != 0))
			in_fence = !in_fence;

		if (!in_fence && footnotes_enabled && is_footnote(document, beg, doc_size, &end, &md->footnotes_found))
			beg = end;
		else if (!in_fence && is_ref(document, beg, doc_size, &end, md->refs))
			beg = end;
		else { /* skipping to the next line */
			end = beg;
			while (end < doc_size && document[end] != '\n' && document[end] != '\r')
				end++;

			/* adding the line body if present */
			if (end > beg)
				expand_tabs(text, document + beg, end - beg);

			while (end < doc_size && (document[end] == '\n' || document[end] == '\r')) {
				/* add one \n per newline */
				if (document[end] == '\n' || (end + 1 < doc_size && document[end + 1] != '\n'))
					bufputc(text, '\n');
				end++;
			}

			beg = end;
		}
	}

	/* pre-grow the output buffer to minimize allocations */
	bufgrow(ob, MARKDOWN_GROW(text->size));

	/* second pass: actual rendering */
	if (md->cb.doc_header)
		md->cb.doc_header(ob, md->opaque);

	if (text->size) {
		/* adding a final newline if not already present */
		if (text->data[text->size - 1] != '\n' && text->data[text->size - 1] != '\r')
			bufputc(text, '\n');

		parse_block(ob, md, text->data, text->size);
	}

	/* footnotes */
	if (footnotes_enabled)
		parse_footnote_list(ob, md, &md->footnotes_used);

	if (md->cb.doc_footer)
		md->cb.doc_footer(ob, md->opaque);

	/* Null-terminate the buffer */
	bufcstr(ob);

	/* clean-up */
	bufrelease(text);
	free_link_refs(md->refs);
	if (footnotes_enabled) {
		free_footnote_list(&md->footnotes_found, 1);
		free_footnote_list(&md->footnotes_used, 0);
	}

	assert(md->work_bufs[BUFFER_SPAN].size == 0);
	assert(md->work_bufs[BUFFER_BLOCK].size == 0);
}