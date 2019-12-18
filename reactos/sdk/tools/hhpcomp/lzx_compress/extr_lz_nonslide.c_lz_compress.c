#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int eofcount; int chars_in_buf; int block_loc; int max_dist; int* lentab; int max_match; int frame_size; int cur_loc; int min_match; scalar_t__ (* output_match ) (TYPE_1__*,int,int) ;int /*<<< orphan*/  (* output_literal ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * block_buf; scalar_t__ stop; int /*<<< orphan*/ ** prevtab; int /*<<< orphan*/  analysis_valid; } ;
typedef  TYPE_1__ lz_info ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fill_blockbuf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int /*<<< orphan*/  lz_analyze_block (TYPE_1__*) ; 
 scalar_t__ lz_left_to_process (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 

int lz_compress(lz_info *lzi, int nchars) 
{

  u_char *bbp, *bbe;
  int *lentab, *lenp;
  u_char **prevtab, **prevp;
  int len;
  int holdback;
  short trimmed;

  lzi->stop = 0;
  while ((lz_left_to_process(lzi) || !lzi->eofcount) && !lzi->stop && nchars > 0) {
#if 1
    if (!lzi->analysis_valid ||
	(!lzi->eofcount &&
	 ((lzi->chars_in_buf- lzi->block_loc) < nchars))) {
      int residual = lzi->chars_in_buf - lzi->block_loc;
      int bytes_to_move = lzi->max_dist + residual;
      if (bytes_to_move > lzi->chars_in_buf)
	bytes_to_move = lzi->chars_in_buf;
#ifdef DEBUG_ANALYZE_BLOCK
      fprintf(stderr, "Moving %06x, chars_in_buf %06x, residual = %06x, nchars= %06x block_loc = %06x\n", bytes_to_move, lzi->chars_in_buf, residual, nchars, lzi->block_loc);
#endif
      memmove(lzi->block_buf, lzi->block_buf + lzi->chars_in_buf - bytes_to_move,
	      bytes_to_move);
      
      lzi->block_loc = bytes_to_move - residual;
      lzi->chars_in_buf = bytes_to_move;
#ifdef DEBUG_ANALYZE_BLOCK
      fprintf(stderr, "New chars_in_buf %06x,  new block_loc = %06x, eof = %1d\n", lzi->chars_in_buf, lzi->block_loc, lzi->eofcount);
#endif
      fill_blockbuf(lzi, nchars);
#ifdef DEBUG_ANALYZE_BLOCK
      fprintf(stderr, "Really new chars_in_buf %06x,  new block_loc = %06x, eof = %1d\n", lzi->chars_in_buf, lzi->block_loc, lzi->eofcount);
#endif
      lz_analyze_block(lzi);
    }
#else
    if (!lzi->analysis_valid ||
	(lzi->block_loc - lzi->chars_in_buf) == 0) {
      lzi->block_loc = 0;
      lzi->chars_in_buf = 0;
      fill_blockbuf(lzi, nchars);
      lz_analyze_block(lzi);
    }
#endif
    prevtab = prevp = lzi->prevtab + lzi->block_loc;
    lentab = lenp = lzi->lentab + lzi->block_loc;
    bbp = lzi->block_buf + lzi->block_loc;
    holdback = lzi->max_match;
    if (lzi->eofcount) holdback = 0;
    if (lzi->chars_in_buf < (nchars + lzi->block_loc))
      bbe = lzi->block_buf + lzi->chars_in_buf - holdback;
    else
      bbe = bbp + nchars;
    while ((bbp < bbe) && (!lzi->stop)) {
      trimmed = 0;
      len = *lenp;
      if (lzi->frame_size && (len > (lzi->frame_size - lzi->cur_loc % lzi->frame_size))) {
#ifdef DEBUG_TRIMMING
	fprintf(stderr, "Trim for framing: %06x %d %d\n", lzi->cur_loc,len, (lzi->frame_size - lzi->cur_loc % lzi->frame_size));
#endif
	trimmed = 1;
	len = (lzi->frame_size - lzi->cur_loc % lzi->frame_size);
      }
      if (len > nchars) {
#ifdef DEBUG_TRIMMING
	fprintf(stderr, "Trim for blocking: %06x %d %d\n", lzi->cur_loc,len, nchars);
#endif
	trimmed = 1;
	len = nchars;
      }
      if (len >= lzi->min_match) {
#ifdef LAZY
	if ((bbp < bbe -1) && !trimmed &&
	    ((lenp[1] > (len + 1)) /* || ((lenp[1] == len) && (prevp[1] > prevp[0])) */)) {
	  len = 1;
	  /* this is the lazy eval case */
	}
	else 
#endif
	  if (lzi->output_match(lzi, (*prevp - lzi->block_buf) - lzi->block_loc,
				len) < 0) {
	    //	    fprintf(stderr, "Match rejected: %06x %d\n", lzi->cur_loc, len);
	    len = 1; /* match rejected */
	  }
      }
      else
	len = 1;
      
      if (len < lzi->min_match) {
	assert(len == 1);
	lzi->output_literal(lzi, *bbp);
      }
      //      fprintf(stderr, "len = %3d, *lenp = %3d, cur_loc = %06x, block_loc = %06x\n", len, *lenp, lzi->cur_loc, lzi->block_loc);
      bbp += len;
      prevp += len;
      lenp += len;
      lzi->cur_loc += len;
      lzi->block_loc += len;
      assert(nchars >= len);
      nchars -= len;

    }
  }
  return 0;
}