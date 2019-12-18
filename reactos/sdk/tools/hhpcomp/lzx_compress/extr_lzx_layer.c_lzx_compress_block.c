#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  long uint32_t ;
struct TYPE_8__ {int block_size; int subdivide; int left_in_block; scalar_t__ left_in_frame; double main_entropy; double last_ratio; int* length_freq_table; int* main_freq_table; int main_tree_size; int* aligned_freq_table; long* prev_main_treelengths; long* prev_length_treelengths; int /*<<< orphan*/ * block_codes; int /*<<< orphan*/ * block_codesp; TYPE_3__* length_tree; TYPE_3__* main_tree; TYPE_3__* aligned_tree; scalar_t__ need_1bit_header; int /*<<< orphan*/  in_arg; scalar_t__ (* at_eof ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  lzi; } ;
typedef  TYPE_1__ lzx_data ;
struct TYPE_9__ {long codelength; } ;

/* Variables and functions */
 int LZX_ALIGNED_OFFSET_BLOCK ; 
 int LZX_ALIGNED_SIZE ; 
 void* LZX_FRAME_SIZE ; 
 int LZX_MAX_CODE_LENGTH ; 
 int LZX_VERBATIM_BLOCK ; 
 int NUM_CHARS ; 
 int NUM_SECONDARY_LENGTHS ; 
 int /*<<< orphan*/  build_huffman_tree (int,int,int*,TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lz_compress (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lz_left_to_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lzx_write_bits (TYPE_1__*,int,long) ; 
 int /*<<< orphan*/  lzx_write_compressed_literals (TYPE_1__*,int) ; 
 int /*<<< orphan*/  lzx_write_compressed_tree (TYPE_1__*,TYPE_3__*,long*,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 

int lzx_compress_block(lzx_data *lzxd, int block_size, int subdivide)
{
  int i;
  uint32_t written_sofar = 0;
  int block_type;
  long uncomp_bits;
  long comp_bits;
  long comp_bits_ovh;
  long uncomp_length;
  
  if ((lzxd->block_size != block_size) || (lzxd->block_codes == NULL)) {
    if (lzxd->block_codes != NULL) free(lzxd->block_codes);
    lzxd->block_size = block_size;
    lzxd->block_codes =  malloc(block_size * sizeof(uint32_t));
  }
  lzxd->subdivide = subdivide?1:0;

  lzxd->left_in_block = block_size;
  lzxd->left_in_frame = LZX_FRAME_SIZE;
  lzxd->main_entropy = 0.0;
  lzxd->last_ratio = 9999999.0;
  lzxd->block_codesp = lzxd->block_codes;

  memset(lzxd->length_freq_table, 0, NUM_SECONDARY_LENGTHS * sizeof(int));
  memset(lzxd->main_freq_table, 0, lzxd->main_tree_size * sizeof(int));
  memset(lzxd->aligned_freq_table, 0, LZX_ALIGNED_SIZE * sizeof(int));
  do {
    lz_compress(lzxd->lzi, lzxd->left_in_block);
    if (lzxd->left_in_frame == 0)
      lzxd->left_in_frame = LZX_FRAME_SIZE;
    
    if ((lzxd->subdivide<0) || !lzxd->left_in_block || 
	(!lz_left_to_process(lzxd->lzi) && lzxd->at_eof(lzxd->in_arg))) {
      /* now one block is LZ-analyzed. */
      /* time to write it out */
      uncomp_length = lzxd->block_size - lzxd->left_in_block - written_sofar;
      /* uncomp_length will sometimes be 0 when input length is 
	 an exact multiple of frame size */
      if (uncomp_length == 0)
	  continue;
      if (lzxd->subdivide < 0) {
#ifdef DEBUG_ENTROPY
	fprintf(stderr, "subdivided\n");
#endif
	lzxd->subdivide = 1;
      }
      
      if (lzxd->need_1bit_header) {
	/* one bit Intel preprocessing header */
	/* always 0 because this implementation doesn't do Intel preprocessing */
	lzx_write_bits(lzxd, 1, 0);
	lzxd->need_1bit_header = 0;
      }

      /* handle extra bits */
      uncomp_bits = comp_bits = 0;
      build_huffman_tree(LZX_ALIGNED_SIZE, 7, lzxd->aligned_freq_table, lzxd->aligned_tree);
      for (i = 0; i < LZX_ALIGNED_SIZE; i++) {
	uncomp_bits += lzxd->aligned_freq_table[i]* 3;
	comp_bits += lzxd->aligned_freq_table[i]* lzxd->aligned_tree[i].codelength;
      }
      comp_bits_ovh = comp_bits + LZX_ALIGNED_SIZE * 3;
      if (comp_bits_ovh < uncomp_bits)
      	block_type = LZX_ALIGNED_OFFSET_BLOCK;
      else
	block_type = LZX_VERBATIM_BLOCK;

#ifdef DEBUG_EXTRA_BITS
      fprintf(stderr, "Extra bits uncompressed: %5d  compressed:  %5d  compressed w/overhead %5d gain/loss %5d\n", uncomp_bits, comp_bits, comp_bits_ovh, uncomp_bits - comp_bits_ovh);
#endif

      /* block type */
      lzx_write_bits(lzxd, 3, block_type);
      /* uncompressed length */
      lzx_write_bits(lzxd, 24, uncomp_length);

      written_sofar = lzxd->block_size - lzxd->left_in_block;

      /* now write out the aligned offset trees if present */
      if (block_type == LZX_ALIGNED_OFFSET_BLOCK) {
	for (i = 0; i < LZX_ALIGNED_SIZE; i++) {
	  lzx_write_bits(lzxd, 3, lzxd->aligned_tree[i].codelength); 
	}
      }
      /* end extra bits */
      build_huffman_tree(lzxd->main_tree_size, LZX_MAX_CODE_LENGTH,
			 lzxd->main_freq_table, lzxd->main_tree);
      build_huffman_tree(NUM_SECONDARY_LENGTHS, 16, 
			 lzxd->length_freq_table, lzxd->length_tree);



      /* now write the pre-tree and tree for main 1 */
      lzx_write_compressed_tree(lzxd, lzxd->main_tree, lzxd->prev_main_treelengths, NUM_CHARS);
    
      /* now write the pre-tree and tree for main 2*/
      lzx_write_compressed_tree(lzxd, lzxd->main_tree + NUM_CHARS,
				lzxd->prev_main_treelengths + NUM_CHARS,
				lzxd->main_tree_size - NUM_CHARS);
      
      /* now write the pre tree and tree for length */
      lzx_write_compressed_tree(lzxd, lzxd->length_tree, lzxd->prev_length_treelengths,
				NUM_SECONDARY_LENGTHS);
      
      /* now write literals */
      lzx_write_compressed_literals(lzxd, block_type);
      
      /* copy treelengths somewhere safe to do delta compression */
      for (i = 0; i < lzxd->main_tree_size; i++) {
	lzxd->prev_main_treelengths[i] = lzxd->main_tree[i].codelength;
      }
      for (i = 0; i < NUM_SECONDARY_LENGTHS; i++) {
	lzxd->prev_length_treelengths[i] = lzxd->length_tree[i].codelength;
      }
      lzxd->main_entropy = 0.0;
      lzxd->last_ratio = 9999999.0;
      lzxd->block_codesp = lzxd->block_codes;
      
      memset(lzxd->length_freq_table, 0, NUM_SECONDARY_LENGTHS * sizeof(int));
      memset(lzxd->main_freq_table, 0, lzxd->main_tree_size * sizeof(int));
      memset(lzxd->aligned_freq_table, 0, LZX_ALIGNED_SIZE * sizeof(int));
    }
  }
  while (lzxd->left_in_block && (lz_left_to_process(lzxd->lzi) || !lzxd->at_eof(lzxd->in_arg)));
  return 0;
}