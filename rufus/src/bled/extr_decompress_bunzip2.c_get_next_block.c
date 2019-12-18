#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct group_data {int minLen; int maxLen; int* base; int* limit; int* permute; } ;
struct TYPE_4__ {int* dbuf; int dbufSize; int* selectors; int headerCRC; int inbufBitCount; scalar_t__ inbufPos; scalar_t__ inbufCount; int inbufBits; int* inbuf; int writeCurrent; int writePos; int writeRunCountdown; int writeCount; struct group_data* groups; int /*<<< orphan*/  jmpbuf; } ;
typedef  TYPE_1__ bunzip_data ;

/* Variables and functions */
 int GROUP_SIZE ; 
 int INT_MAX ; 
 int MAX_GROUPS ; 
 int MAX_HUFCODE_BITS ; 
 int MAX_SYMBOLS ; 
 int RETVAL_DATA_ERROR ; 
 int RETVAL_LAST_BLOCK ; 
 int RETVAL_NOT_BZIP_DATA ; 
 int RETVAL_OBSOLETE_INPUT ; 
 int RETVAL_OK ; 
 unsigned int SYMBOL_RUNB ; 
 int /*<<< orphan*/  dbg (char*,int,int,int,int) ; 
 int get_bits (TYPE_1__*,int) ; 
 int setjmp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_next_block(bunzip_data *bd)
{
	struct group_data *hufGroup;
	int dbufCount, dbufSize, groupCount, *base, *limit, selector,
		i, j, t, runPos, symCount, symTotal, nSelectors, byteCount[256];
	int runCnt;
	uint8_t uc, symToByte[256], mtfSymbol[256], *selectors;
	uint32_t *dbuf;
	unsigned origPtr;

	dbuf = bd->dbuf;
	dbufSize = bd->dbufSize;
	selectors = bd->selectors;

/* In bbox, we are ok with aborting through setjmp which is set up in start_bunzip */
#if 0
	/* Reset longjmp I/O error handling */
	i = setjmp(bd->jmpbuf);
	if (i) return i;
#endif

	/* Read in header signature and CRC, then validate signature.
	   (last block signature means CRC is for whole file, return now) */
	i = get_bits(bd, 24);
	j = get_bits(bd, 24);
	bd->headerCRC = get_bits(bd, 32);
	if ((i == 0x177245) && (j == 0x385090)) return RETVAL_LAST_BLOCK;
	if ((i != 0x314159) || (j != 0x265359)) return RETVAL_NOT_BZIP_DATA;

	/* We can add support for blockRandomised if anybody complains.  There was
	   some code for this in busybox 1.0.0-pre3, but nobody ever noticed that
	   it didn't actually work. */
	if (get_bits(bd, 1)) return RETVAL_OBSOLETE_INPUT;
	origPtr = get_bits(bd, 24);
	if ((int)origPtr > dbufSize) return RETVAL_DATA_ERROR;

	/* mapping table: if some byte values are never used (encoding things
	   like ascii text), the compression code removes the gaps to have fewer
	   symbols to deal with, and writes a sparse bitfield indicating which
	   values were present.  We make a translation table to convert the symbols
	   back to the corresponding bytes. */
	symTotal = 0;
	i = 0;
	t = get_bits(bd, 16);
	do {
		if (t & (1 << 15)) {
			unsigned inner_map = get_bits(bd, 16);
			do {
				if (inner_map & (1 << 15))
					symToByte[symTotal++] = i;
				inner_map <<= 1;
				i++;
			} while (i & 15);
			i -= 16;
		}
		t <<= 1;
		i += 16;
	} while (i < 256);

	/* How many different Huffman coding groups does this block use? */
	groupCount = get_bits(bd, 3);
	if (groupCount < 2 || groupCount > MAX_GROUPS)
		return RETVAL_DATA_ERROR;

	/* nSelectors: Every GROUP_SIZE many symbols we select a new Huffman coding
	   group.  Read in the group selector list, which is stored as MTF encoded
	   bit runs.  (MTF=Move To Front, as each value is used it's moved to the
	   start of the list.) */
	for (i = 0; i < groupCount; i++)
		mtfSymbol[i] = i;
	nSelectors = get_bits(bd, 15);
	if (!nSelectors)
		return RETVAL_DATA_ERROR;
	for (i = 0; i < nSelectors; i++) {
		uint8_t tmp_byte;
		/* Get next value */
		int n = 0;
		while (get_bits(bd, 1)) {
			if (n >= groupCount) return RETVAL_DATA_ERROR;
			n++;
		}
		/* Decode MTF to get the next selector */
		tmp_byte = mtfSymbol[n];
		while (--n >= 0)
			mtfSymbol[n + 1] = mtfSymbol[n];
		mtfSymbol[0] = selectors[i] = tmp_byte;
	}

	/* Read the Huffman coding tables for each group, which code for symTotal
	   literal symbols, plus two run symbols (RUNA, RUNB) */
	symCount = symTotal + 2;
	for (j = 0; j < groupCount; j++) {
		uint8_t length[MAX_SYMBOLS];
		/* 8 bits is ALMOST enough for temp[], see below */
		unsigned temp[MAX_HUFCODE_BITS+1];
		int minLen, maxLen, pp, len_m1;

		/* Read Huffman code lengths for each symbol.  They're stored in
		   a way similar to mtf; record a starting value for the first symbol,
		   and an offset from the previous value for every symbol after that.
		   (Subtracting 1 before the loop and then adding it back at the end is
		   an optimization that makes the test inside the loop simpler: symbol
		   length 0 becomes negative, so an unsigned inequality catches it.) */
		len_m1 = get_bits(bd, 5) - 1;
		for (i = 0; i < symCount; i++) {
			for (;;) {
				int two_bits;
				if ((unsigned)len_m1 > (MAX_HUFCODE_BITS-1))
					return RETVAL_DATA_ERROR;

				/* If first bit is 0, stop.  Else second bit indicates whether
				   to increment or decrement the value.  Optimization: grab 2
				   bits and unget the second if the first was 0. */
				two_bits = get_bits(bd, 2);
				if (two_bits < 2) {
					bd->inbufBitCount++;
					break;
				}

				/* Add one if second bit 1, else subtract 1.  Avoids if/else */
				len_m1 += (((two_bits+1) & 2) - 1);
			}

			/* Correct for the initial -1, to get the final symbol length */
			length[i] = len_m1 + 1;
		}

		/* Find largest and smallest lengths in this group */
		minLen = maxLen = length[0];
		for (i = 1; i < symCount; i++) {
			if (length[i] > maxLen) maxLen = length[i];
			else if (length[i] < minLen) minLen = length[i];
		}

		/* Calculate permute[], base[], and limit[] tables from length[].
		 *
		 * permute[] is the lookup table for converting Huffman coded symbols
		 * into decoded symbols.  base[] is the amount to subtract from the
		 * value of a Huffman symbol of a given length when using permute[].
		 *
		 * limit[] indicates the largest numerical value a symbol with a given
		 * number of bits can have.  This is how the Huffman codes can vary in
		 * length: each code with a value>limit[length] needs another bit.
		 */
		hufGroup = bd->groups + j;
		hufGroup->minLen = minLen;
		hufGroup->maxLen = maxLen;

		/* Note that minLen can't be smaller than 1, so we adjust the base
		   and limit array pointers so we're not always wasting the first
		   entry.  We do this again when using them (during symbol decoding). */
		base = hufGroup->base - 1;
		limit = hufGroup->limit - 1;

		/* Calculate permute[].  Concurently, initialize temp[] and limit[]. */
		pp = 0;
		for (i = minLen; i <= maxLen; i++) {
			int k;
			temp[i] = limit[i] = 0;
			for (k = 0; k < symCount; k++)
				if (length[k] == i)
					hufGroup->permute[pp++] = k;
		}

		/* Count symbols coded for at each bit length */
		/* NB: in pathological cases, temp[8] can end ip being 256.
		 * That's why uint8_t is too small for temp[]. */
		for (i = 0; i < symCount; i++) temp[length[i]]++;

		/* Calculate limit[] (the largest symbol-coding value at each bit
		 * length, which is (previous limit<<1)+symbols at this level), and
		 * base[] (number of symbols to ignore at each bit length, which is
		 * limit minus the cumulative count of symbols coded for already). */
		pp = t = 0;
		for (i = minLen; i < maxLen;) {
			unsigned temp_i = temp[i];

			pp += temp_i;

			/* We read the largest possible symbol size and then unget bits
			   after determining how many we need, and those extra bits could
			   be set to anything.  (They're noise from future symbols.)  At
			   each level we're really only interested in the first few bits,
			   so here we set all the trailing to-be-ignored bits to 1 so they
			   don't affect the value>limit[length] comparison. */
			limit[i] = (pp << (maxLen - i)) - 1;
			pp <<= 1;
			t += temp_i;
			base[++i] = pp - t;
		}
		limit[maxLen] = pp + temp[maxLen] - 1;
		limit[maxLen+1] = INT_MAX; /* Sentinel value for reading next sym. */
		base[minLen] = 0;
	}

	/* We've finished reading and digesting the block header.  Now read this
	   block's Huffman coded symbols from the file and undo the Huffman coding
	   and run length encoding, saving the result into dbuf[dbufCount++] = uc */

	/* Initialize symbol occurrence counters and symbol Move To Front table */
	/*memset(byteCount, 0, sizeof(byteCount)); - smaller, but slower */
	for (i = 0; i < 256; i++) {
		byteCount[i] = 0;
		mtfSymbol[i] = (uint8_t)i;
	}

	/* Loop through compressed symbols. */

	runPos = dbufCount = selector = 0;
	for (;;) {
		int nextSym;

		/* Fetch next Huffman coding group from list. */
		symCount = GROUP_SIZE - 1;
		if (selector >= nSelectors) return RETVAL_DATA_ERROR;
		hufGroup = bd->groups + selectors[selector++];
		base = hufGroup->base - 1;
		limit = hufGroup->limit - 1;

 continue_this_group:
		/* Read next Huffman-coded symbol. */

		/* Note: It is far cheaper to read maxLen bits and back up than it is
		   to read minLen bits and then add additional bit at a time, testing
		   as we go.  Because there is a trailing last block (with file CRC),
		   there is no danger of the overread causing an unexpected EOF for a
		   valid compressed file.
		 */
		if (1) {
			/* As a further optimization, we do the read inline
			   (falling back to a call to get_bits if the buffer runs dry).
			 */
			int new_cnt;
			while ((new_cnt = bd->inbufBitCount - hufGroup->maxLen) < 0) {
				/* bd->inbufBitCount < hufGroup->maxLen */
				if (bd->inbufPos == bd->inbufCount) {
					nextSym = get_bits(bd, hufGroup->maxLen);
					goto got_huff_bits;
				}
				bd->inbufBits = (bd->inbufBits << 8) | bd->inbuf[bd->inbufPos++];
				bd->inbufBitCount += 8;
			};
			bd->inbufBitCount = new_cnt; /* "bd->inbufBitCount -= hufGroup->maxLen;" */
			nextSym = (bd->inbufBits >> new_cnt) & ((1 << hufGroup->maxLen) - 1);
 got_huff_bits: ;
		} else { /* unoptimized equivalent */
			nextSym = get_bits(bd, hufGroup->maxLen);
		}
		/* Figure how many bits are in next symbol and unget extras */
		i = hufGroup->minLen;
		while (nextSym > limit[i]) ++i;
		j = hufGroup->maxLen - i;
		if (j < 0)
			return RETVAL_DATA_ERROR;
		bd->inbufBitCount += j;

		/* Huffman decode value to get nextSym (with bounds checking) */
		nextSym = (nextSym >> j) - base[i];
		if ((unsigned)nextSym >= MAX_SYMBOLS)
			return RETVAL_DATA_ERROR;
		nextSym = hufGroup->permute[nextSym];

		/* We have now decoded the symbol, which indicates either a new literal
		   byte, or a repeated run of the most recent literal byte.  First,
		   check if nextSym indicates a repeated run, and if so loop collecting
		   how many times to repeat the last literal. */
		if ((unsigned)nextSym <= SYMBOL_RUNB) { /* RUNA or RUNB */

			/* If this is the start of a new run, zero out counter */
			if (runPos == 0) {
				runPos = 1;
				runCnt = 0;
			}

			/* Neat trick that saves 1 symbol: instead of or-ing 0 or 1 at
			   each bit position, add 1 or 2 instead.  For example,
			   1011 is 1<<0 + 1<<1 + 2<<2.  1010 is 2<<0 + 2<<1 + 1<<2.
			   You can make any bit pattern that way using 1 less symbol than
			   the basic or 0/1 method (except all bits 0, which would use no
			   symbols, but a run of length 0 doesn't mean anything in this
			   context).  Thus space is saved. */
			runCnt += (runPos << nextSym); /* +runPos if RUNA; +2*runPos if RUNB */
			if (runPos < dbufSize) runPos <<= 1;
			goto end_of_huffman_loop;
		}

		/* When we hit the first non-run symbol after a run, we now know
		   how many times to repeat the last literal, so append that many
		   copies to our buffer of decoded symbols (dbuf) now.  (The last
		   literal used is the one at the head of the mtfSymbol array.) */
		if (runPos != 0) {
			uint8_t tmp_byte;
			if (dbufCount + runCnt > dbufSize) {
				dbg("dbufCount:%d+runCnt:%d %d > dbufSize:%d RETVAL_DATA_ERROR",
						dbufCount, runCnt, dbufCount + runCnt, dbufSize);
				return RETVAL_DATA_ERROR;
			}
			tmp_byte = symToByte[mtfSymbol[0]];
			byteCount[tmp_byte] += runCnt;
			while (--runCnt >= 0) dbuf[dbufCount++] = (uint32_t)tmp_byte;
			runPos = 0;
		}

		/* Is this the terminating symbol? */
		if (nextSym > symTotal) break;

		/* At this point, nextSym indicates a new literal character.  Subtract
		   one to get the position in the MTF array at which this literal is
		   currently to be found.  (Note that the result can't be -1 or 0,
		   because 0 and 1 are RUNA and RUNB.  But another instance of the
		   first symbol in the mtf array, position 0, would have been handled
		   as part of a run above.  Therefore 1 unused mtf position minus
		   2 non-literal nextSym values equals -1.) */
		if (dbufCount >= dbufSize) return RETVAL_DATA_ERROR;
		i = nextSym - 1;
		uc = mtfSymbol[i];

		/* Adjust the MTF array.  Since we typically expect to move only a
		 * small number of symbols, and are bound by 256 in any case, using
		 * memmove here would typically be bigger and slower due to function
		 * call overhead and other assorted setup costs. */
		do {
			mtfSymbol[i] = mtfSymbol[i-1];
		} while (--i);
		mtfSymbol[0] = uc;
		uc = symToByte[uc];

		/* We have our literal byte.  Save it into dbuf. */
		byteCount[uc]++;
		dbuf[dbufCount++] = (uint32_t)uc;

		/* Skip group initialization if we're not done with this group.  Done
		 * this way to avoid compiler warning. */
 end_of_huffman_loop:
		if (--symCount >= 0) goto continue_this_group;
	}

	/* At this point, we've read all the Huffman-coded symbols (and repeated
	   runs) for this block from the input stream, and decoded them into the
	   intermediate buffer.  There are dbufCount many decoded bytes in dbuf[].
	   Now undo the Burrows-Wheeler transform on dbuf.
	   See http://dogma.net/markn/articles/bwt/bwt.htm
	 */

	/* Turn byteCount into cumulative occurrence counts of 0 to n-1. */
	j = 0;
	for (i = 0; i < 256; i++) {
		int tmp_count = j + byteCount[i];
		byteCount[i] = j;
		j = tmp_count;
	}

	/* Figure out what order dbuf would be in if we sorted it. */
	for (i = 0; i < dbufCount; i++) {
		uint8_t tmp_byte = (uint8_t)dbuf[i];
		int tmp_count = byteCount[tmp_byte];
		dbuf[tmp_count] |= (i << 8);
		byteCount[tmp_byte] = tmp_count + 1;
	}

	/* Decode first byte by hand to initialize "previous" byte.  Note that it
	   doesn't get output, and if the first three characters are identical
	   it doesn't qualify as a run (hence writeRunCountdown=5). */
	if (dbufCount) {
		uint32_t tmp;
		if ((int)origPtr >= dbufCount) return RETVAL_DATA_ERROR;
		tmp = dbuf[origPtr];
		bd->writeCurrent = (uint8_t)tmp;
		bd->writePos = (tmp >> 8);
		bd->writeRunCountdown = 5;
	}
	bd->writeCount = dbufCount;

	return RETVAL_OK;
}