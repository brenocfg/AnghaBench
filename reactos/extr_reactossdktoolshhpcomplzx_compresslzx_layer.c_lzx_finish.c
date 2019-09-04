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
struct lzx_results {int /*<<< orphan*/  len_uncompressed_input; int /*<<< orphan*/  len_compressed_output; } ;
struct lzx_data {struct lzx_data* main_freq_table; struct lzx_data* main_tree; struct lzx_data* prev_main_treelengths; struct lzx_data* lzi; int /*<<< orphan*/  len_uncompressed_input; int /*<<< orphan*/  len_compressed_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lzx_data*) ; 
 int /*<<< orphan*/  lz_release (struct lzx_data*) ; 

int lzx_finish(struct lzx_data *lzxd, struct lzx_results *lzxr)
{
  /*  lzx_align_output(lzxd);  Not needed as long as frame padding is in place */
  if (lzxr) {
    lzxr->len_compressed_output = lzxd->len_compressed_output;
    lzxr->len_uncompressed_input = lzxd->len_uncompressed_input;
  }
  lz_release(lzxd->lzi);
  free(lzxd->lzi);
  free(lzxd->prev_main_treelengths);
  free(lzxd->main_tree);
  free(lzxd->main_freq_table);
  free(lzxd);
  return 0;
}