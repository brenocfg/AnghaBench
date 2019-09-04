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
typedef  int /*<<< orphan*/  uint8_t ;
struct lzx_data {int num_position_slots; int main_tree_size; scalar_t__ len_compressed_output; scalar_t__ len_uncompressed_input; void* lzi; void* prev_main_treelengths; void* main_tree; void* main_freq_table; int /*<<< orphan*/ * block_codes; scalar_t__ bits_in_buf; int /*<<< orphan*/  mark_frame; int /*<<< orphan*/  at_eof; int /*<<< orphan*/  put_bytes; int /*<<< orphan*/  get_bytes; void* mark_frame_arg; void* out_arg; void* in_arg; } ;
typedef  int /*<<< orphan*/  lzx_put_bytes_t ;
typedef  int /*<<< orphan*/  lzx_mark_frame_t ;
typedef  int /*<<< orphan*/  lzx_get_bytes_t ;
typedef  int /*<<< orphan*/  lzx_at_eof_t ;
typedef  int /*<<< orphan*/  huff_entry ;

/* Variables and functions */
 int /*<<< orphan*/  LZX_FRAME_SIZE ; 
 int /*<<< orphan*/  MAX_MATCH ; 
 int /*<<< orphan*/  MIN_MATCH ; 
 int NUM_CHARS ; 
 int /*<<< orphan*/  lz_init (void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lzx_data*) ; 
 int /*<<< orphan*/  lzx_get_chars ; 
 int /*<<< orphan*/  lzx_init_static () ; 
 int /*<<< orphan*/  lzx_output_literal ; 
 int /*<<< orphan*/  lzx_output_match ; 
 int /*<<< orphan*/  lzx_reset (struct lzx_data*) ; 
 void* malloc (int) ; 
 int* num_position_slots ; 

int lzx_init(struct lzx_data **lzxdp, int wsize_code, 
	     lzx_get_bytes_t get_bytes, void *get_bytes_arg,
	     lzx_at_eof_t at_eof,
	     lzx_put_bytes_t put_bytes, void *put_bytes_arg,
	     lzx_mark_frame_t mark_frame, void *mark_frame_arg)
{
  int wsize;
  struct lzx_data *lzxd;

  if ((wsize_code < 15) || (wsize_code > 21)) {
    return -1;
  }
  lzx_init_static();

  *lzxdp = lzxd = malloc(sizeof(*lzxd));
  if (lzxd == 0)
    return -2;

  lzxd->in_arg = get_bytes_arg;
  lzxd->out_arg = put_bytes_arg;
  lzxd->mark_frame_arg = mark_frame_arg;
  lzxd->get_bytes = get_bytes;
  lzxd->put_bytes = put_bytes;
  lzxd->at_eof = at_eof;
  lzxd->mark_frame = mark_frame;

  wsize = 1 << (wsize_code);

  lzxd->bits_in_buf = 0;
  lzxd->block_codes = NULL;
  lzxd->num_position_slots = num_position_slots[wsize_code-15];
  lzxd->main_tree_size = (NUM_CHARS + 8 * lzxd->num_position_slots);

  lzxd->main_freq_table = malloc(sizeof(int) * lzxd->main_tree_size);
  lzxd->main_tree = malloc(sizeof(huff_entry)* lzxd->main_tree_size);
  lzxd->prev_main_treelengths = malloc(sizeof(uint8_t)*lzxd->main_tree_size);

  lzxd->lzi = malloc(sizeof (*lzxd->lzi));
  /* the -3 prevents matches at wsize, wsize-1, wsize-2, all of which are illegal */
  lz_init(lzxd->lzi, wsize, wsize - 3, MAX_MATCH, MIN_MATCH, LZX_FRAME_SIZE,
	  lzx_get_chars, lzx_output_match, lzx_output_literal,lzxd);
  lzxd->len_uncompressed_input = 0;
  lzxd->len_compressed_output = 0;
  lzx_reset(lzxd);
  return 0;
}