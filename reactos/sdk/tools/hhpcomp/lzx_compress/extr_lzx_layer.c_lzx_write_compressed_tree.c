#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int u_char ;
struct lzx_data {int dummy; } ;
struct huff_entry {int codelength; } ;
struct TYPE_3__ {int codelength; int code; } ;
typedef  TYPE_1__ huff_entry ;
typedef  int /*<<< orphan*/  freqs ;

/* Variables and functions */
 int LZX_PRETREE_SIZE ; 
 int /*<<< orphan*/  build_huffman_tree (int,int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  lzx_write_bits (struct lzx_data*,int,int) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int 
lzx_write_compressed_tree(struct lzx_data *lzxd,
			  struct huff_entry *tree, uint8_t *prevlengths,
			  int treesize)
{
  u_char *codes;
  u_char *runs;
  int freqs[LZX_PRETREE_SIZE];
  int cur_run;
  int last_len;
  huff_entry pretree[20];
  u_char *codep;
  u_char *codee;
  u_char *runp;
  int excess;
  int i;
  int cur_code;

  codep = codes = malloc(treesize*sizeof(char));
  runp = runs = malloc(treesize*sizeof(char));
  memset(freqs, 0, sizeof(freqs));
  cur_run = 1;
  last_len = tree[0].codelength;
  for (i = 1; i <= treesize; i++) {
    if ((i == treesize) || (tree[i].codelength != last_len)) {
      if (last_len == 0) {
	while (cur_run >= 20) {
	  excess =  cur_run - 20;
	  if (excess > 31) excess = 31;
	  *codep++ = 18;
	  *runp++ = excess;
	  cur_run -= excess + 20;
	  freqs[18]++;
	}
	while (cur_run >= 4) {
	  excess =  cur_run - 4;
	  if (excess > 15) excess = 15;
	  *codep++ = 17;
	  *runp++ = excess;
	  cur_run -= excess + 4;
	  freqs[17]++;
	}
	while (cur_run > 0) {
	  *codep = prevlengths[i - cur_run];
	  freqs[*codep++]++;
	  *runp++ = 0; /* not necessary */
	  cur_run--;
	}
      }
      else {
	while (cur_run >= 4) {
	  if (cur_run == 4) excess = 0;
	  else excess = 1;
	  *codep++ = 19;
	  *runp++ = excess;
	  freqs[19]++;
	  /* right, MS lies again.  Code is NOT 
	     prev_len + len (mod 17), it's prev_len - len (mod 17)*/
	  *codep = prevlengths[i-cur_run] - last_len;
	  if (*codep > 16) *codep += 17;
	  freqs[*codep++]++;
	  *runp++ = 0; /* not necessary */
	  cur_run -= excess+4;
	}
	while (cur_run > 0) {
	  *codep = prevlengths[i-cur_run] - last_len;
	  if (*codep > 16) *codep += 17;
	  *runp++ = 0; /* not necessary */
	  cur_run--;
	  freqs[*codep++]++;
	}
      }
      if (i != treesize)
	last_len = tree[i].codelength;
      cur_run = 0;
    }
    cur_run++;
  }
  codee = codep;
#ifdef DEBUG_TREE_COMPRESSION
  *codep++ = 255;
  *runp++ = 255;
  fprintf(stderr, "num:  len  code  run\n");
  for (i = 0; i < treesize; i++) {
    fprintf(stderr, "%3d:  %2d   %2d    %2d\n", i, tree[i].codelength, codes[i], runs[i]);
  }
#endif
  /* now create the huffman table and write out the pretree */
  build_huffman_tree(LZX_PRETREE_SIZE, 16, freqs, pretree);
  for (i = 0; i < LZX_PRETREE_SIZE; i++) {
    lzx_write_bits(lzxd, 4, pretree[i].codelength);
  }
  codep = codes;
  runp = runs;
  cur_run = 0;
  while (codep < codee) {
    cur_code = *codep++;
    lzx_write_bits(lzxd, pretree[cur_code].codelength, pretree[cur_code].code);
    if (cur_code == 17) {
      cur_run += *runp + 4;
      lzx_write_bits(lzxd, 4, *runp);
    }
    else if (cur_code == 18) {
      cur_run += *runp + 20;
      lzx_write_bits(lzxd, 5, *runp);
    }
    else if (cur_code == 19) {
      cur_run += *runp + 4;
      lzx_write_bits(lzxd, 1, *runp);
      cur_code = *codep++;
      lzx_write_bits(lzxd, pretree[cur_code].codelength, pretree[cur_code].code);
      runp++;
    }
    else {
      cur_run++;
    }
    runp++;
  }
  free(codes);
  free(runs);
  return 0;
}