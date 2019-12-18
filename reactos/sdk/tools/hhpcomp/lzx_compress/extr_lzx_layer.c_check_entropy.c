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
struct TYPE_3__ {int* main_freq_table; double main_entropy; int block_codesp; int block_codes; int left_in_block; int main_tree_size; double last_ratio; int subdivide; int /*<<< orphan*/  lzi; } ;
typedef  TYPE_1__ lzx_data ;

/* Variables and functions */
 int NUM_CHARS ; 
 int NUM_SECONDARY_LENGTHS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 double log (double) ; 
 int /*<<< orphan*/  lz_stop_compressing (int /*<<< orphan*/ ) ; 
 double rloge2 ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void check_entropy(lzx_data *lzud, int main_index) 
{
  /* entropy = - sum_alphabet P(x) * log2 P(x) */
  /* entropy = - sum_alphabet f(x)/N * log2 (f(x)/N) */
  /* entropy = - 1/N sum_alphabet f(x) * (log2 f(x) - log2 N) */
  /* entropy = - 1/N (sum_alphabet f(x) * log2 f(x)) - sum_alphabet f(x) log2 N */
  /* entropy = - 1/N (sum_alphabet f(x) * log2 f(x)) - log2 N sum_alphabet f(x)  */
  /* entropy = - 1/N (sum_alphabet f(x) * log2 f(x)) - N * log2 N   */
  
  /* entropy = - 1/N ((sum_alphabet f(x) * log2 f(x) ) - N * log2 N) */
  /* entropy = - 1/N ((sum_alphabet f(x) * ln f(x) * 1/ln 2) - N * ln N * 1/ln 2) */
  /* entropy = 1/(N ln 2) (N * ln N - (sum_alphabet f(x) * ln f(x))) */
  /* entropy = 1/(N ln 2) (N * ln N + (sum_alphabet -f(x) * ln f(x))) */
  
  /* entropy = 1/(N ln 2) ( sum_alphabet ln N * f(x) + (sum_alphabet -f(x) * ln f(x))) */
  /* entropy = 1/(N ln 2) ( sum_alphabet ln N * f(x) +  (-f(x) * ln f(x))) */
  /* entropy = -1/(N ln 2) ( sum_alphabet -ln N * f(x) +  (f(x) * ln f(x))) */
  /* entropy = -1/(N ln 2) ( sum_alphabet f(x)(- ln N  + ln f(x))) */
  /* entropy = -1/(N ln 2) ( sum_alphabet f(x)(ln f(x)/N)) */
  /* entropy = -1/N  ( sum_alphabet (1/(ln 2))f(x)(ln f(x)/N)) */
  /* entropy = -1/N  ( sum_alphabet f(x)(log2 f(x)/N)) */
  /* entropy = -  ( sum_alphabet f(x)/N(log2 f(x)/N)) */
  /* entropy = -  ( sum_alphabet P(x)(log2 P(x))) */
  

    double freq;
    double n_ln_n;
    double rn_ln2;
    double cur_ratio;
    int n;
    
    /* delete old entropy accumulation */
    if (lzud->main_freq_table[main_index] != 1) {
      freq = (double)lzud->main_freq_table[main_index]-1;
      lzud->main_entropy += freq * log(freq);
    }
    /* add new entropy accumulation */
    freq = (double)lzud->main_freq_table[main_index];
    lzud->main_entropy -= freq * log(freq);
    n = lzud->block_codesp - lzud->block_codes;

    if (((n & 0xFFF) == 0) && (lzud->left_in_block >= 0x1000)) {
      n_ln_n = (double)n * log((double)n);
      rn_ln2 = rloge2 / (double)n;
      cur_ratio = (n * rn_ln2 *(n_ln_n + lzud->main_entropy) + 24 + 3 * 80 + NUM_CHARS + (lzud->main_tree_size-NUM_CHARS)*3 + NUM_SECONDARY_LENGTHS ) / (double)n;
#ifdef DEBUG_ENTROPY
      fprintf(stderr, "n = %d\n", n);
      fprintf(stderr, "main entropy = %f\n", rn_ln2 *(n_ln_n + lzud->main_entropy) );
      fprintf(stderr, "compression ratio (raw) = %f\n", 100.0 * rn_ln2 *(n_ln_n + lzud->main_entropy) /9.0 );
      fprintf(stderr, "compression ratio (ovh) = %f\n", 100.0 * cur_ratio/9.0);
#endif
      if (cur_ratio > lzud->last_ratio) {
#ifdef DEBUG_ENTROPY
	fprintf(stderr, "resetting huffman tables at %d\n", n);
#endif
	lzud->subdivide = -1;
	lz_stop_compressing(lzud->lzi);
      }
      lzud->last_ratio = cur_ratio;
    }
}