#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int prev; unsigned char first_char; int length; unsigned char value; } ;
typedef  TYPE_1__ lzw_code ;
struct TYPE_9__ {unsigned char* rp; unsigned char* wp; int pos; TYPE_3__* state; } ;
typedef  TYPE_2__ fz_stream ;
struct TYPE_10__ {unsigned char* buffer; int code_bits; int code; int old_code; int next_code; unsigned char* rp; unsigned char* wp; int eod; int min_bits; int early_change; unsigned char* bp; int /*<<< orphan*/  old_tiff; int /*<<< orphan*/  chain; scalar_t__ reverse_bits; TYPE_1__* table; } ;
typedef  TYPE_3__ fz_lzwd ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int LZW_CLEAR (TYPE_3__*) ; 
 int LZW_EOD (TYPE_3__*) ; 
 int LZW_FIRST (TYPE_3__*) ; 
 int MAX_BITS ; 
 int MAX_LENGTH ; 
 int NUM_CODES ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fz_is_eof_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fz_read_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fz_read_rbits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
next_lzwd(fz_context *ctx, fz_stream *stm, size_t len)
{
	fz_lzwd *lzw = stm->state;
	lzw_code *table = lzw->table;
	unsigned char *buf = lzw->buffer;
	unsigned char *p = buf;
	unsigned char *ep;
	unsigned char *s;
	int codelen;

	int code_bits = lzw->code_bits;
	int code = lzw->code;
	int old_code = lzw->old_code;
	int next_code = lzw->next_code;

	if (len > sizeof(lzw->buffer))
		len = sizeof(lzw->buffer);
	ep = buf + len;

	while (lzw->rp < lzw->wp && p < ep)
		*p++ = *lzw->rp++;

	while (p < ep)
	{
		if (lzw->eod)
			return EOF;

		if (lzw->reverse_bits)
			code = fz_read_rbits(ctx, lzw->chain, code_bits);
		else
			code = fz_read_bits(ctx, lzw->chain, code_bits);

		if (fz_is_eof_bits(ctx, lzw->chain))
		{
			lzw->eod = 1;
			break;
		}

		if (code == LZW_EOD(lzw))
		{
			lzw->eod = 1;
			break;
		}

		/* Old Tiffs are allowed to NOT send the clear code, and to
		 * overrun at the end. */
		if (!lzw->old_tiff && next_code > NUM_CODES && code != LZW_CLEAR(lzw))
		{
			fz_warn(ctx, "missing clear code in lzw decode");
			code = LZW_CLEAR(lzw);
		}

		if (code == LZW_CLEAR(lzw))
		{
			code_bits = lzw->min_bits;
			next_code = LZW_FIRST(lzw);
			old_code = -1;
			continue;
		}

		/* if stream starts without a clear code, old_code is undefined... */
		if (old_code == -1)
		{
			old_code = code;
		}
		else if (!lzw->old_tiff && next_code == NUM_CODES)
		{
			/* TODO: Ghostscript checks for a following clear code before tolerating */
			fz_warn(ctx, "tolerating a single out of range code in lzw decode");
			next_code++;
		}
		else if (code > next_code || (!lzw->old_tiff && next_code >= NUM_CODES))
		{
			fz_warn(ctx, "out of range code encountered in lzw decode");
		}
		else if (next_code < NUM_CODES)
		{
			/* add new entry to the code table */
			table[next_code].prev = old_code;
			table[next_code].first_char = table[old_code].first_char;
			table[next_code].length = table[old_code].length + 1;
			if (code < next_code)
				table[next_code].value = table[code].first_char;
			else if (code == next_code)
				table[next_code].value = table[next_code].first_char;
			else
				fz_warn(ctx, "out of range code encountered in lzw decode");

			next_code ++;

			if (next_code > (1 << code_bits) - lzw->early_change - 1)
			{
				code_bits ++;
				if (code_bits > MAX_BITS)
					code_bits = MAX_BITS;
			}

			old_code = code;
		}

		/* code maps to a string, copy to output (in reverse...) */
		if (code >= LZW_CLEAR(lzw))
		{
			codelen = table[code].length;
			lzw->rp = lzw->bp;
			lzw->wp = lzw->bp + codelen;

			assert(codelen < MAX_LENGTH);

			s = lzw->wp;
			do {
				*(--s) = table[code].value;
				code = table[code].prev;
			} while (code >= 0 && s > lzw->bp);
		}

		/* ... or just a single character */
		else
		{
			lzw->bp[0] = code;
			lzw->rp = lzw->bp;
			lzw->wp = lzw->bp + 1;
		}

		/* copy to output */
		while (lzw->rp < lzw->wp && p < ep)
			*p++ = *lzw->rp++;
	}

	lzw->code_bits = code_bits;
	lzw->code = code;
	lzw->old_code = old_code;
	lzw->next_code = next_code;

	stm->rp = buf;
	stm->wp = p;
	if (buf == p)
		return EOF;
	stm->pos += p - buf;

	return *stm->rp++;
}