#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  WebPEncodingError ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * histograms; } ;
typedef  TYPE_1__ VP8LHistogramSet ;
typedef  int /*<<< orphan*/  VP8LHashChain ;
typedef  int /*<<< orphan*/  VP8LBitWriter ;
typedef  int /*<<< orphan*/  VP8LBackwardRefs ;
struct TYPE_12__ {int num_symbols; int /*<<< orphan*/ * const codes; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  HuffmanTreeToken ;
typedef  TYPE_2__ HuffmanTreeCode ;
typedef  int /*<<< orphan*/  HuffmanTree ;

/* Variables and functions */
 unsigned long long CODE_LENGTH_CODES ; 
 int /*<<< orphan*/  ClearHuffmanTreeIfOnlyOneSymbol (TYPE_2__* const) ; 
 int /*<<< orphan*/  GetHuffBitLengthsAndCodes (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  StoreHuffmanCode (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ *,TYPE_2__* const) ; 
 int /*<<< orphan*/  StoreImageToBitMask (int /*<<< orphan*/ * const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 TYPE_1__* VP8LAllocateHistogramSet (int,int) ; 
 int /*<<< orphan*/  VP8LFreeHistogramSet (TYPE_1__*) ; 
 int /*<<< orphan*/ * VP8LGetBackwardReferences (int,int,int /*<<< orphan*/  const* const,int,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  VP8LHashChainFill (int /*<<< orphan*/ * const,int,int /*<<< orphan*/  const* const,int,int,int) ; 
 int /*<<< orphan*/  VP8LHistogramSetClear (TYPE_1__*) ; 
 int /*<<< orphan*/  VP8LHistogramStoreRefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP8LPutBits (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VP8_ENC_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VP8_ENC_OK ; 
 int /*<<< orphan*/  WebPSafeFree (int /*<<< orphan*/ * const) ; 
 scalar_t__ WebPSafeMalloc (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int kLZ77RLE ; 
 int kLZ77Standard ; 

__attribute__((used)) static WebPEncodingError EncodeImageNoHuffman(VP8LBitWriter* const bw,
                                              const uint32_t* const argb,
                                              VP8LHashChain* const hash_chain,
                                              VP8LBackwardRefs* const refs_tmp1,
                                              VP8LBackwardRefs* const refs_tmp2,
                                              int width, int height,
                                              int quality, int low_effort) {
  int i;
  int max_tokens = 0;
  WebPEncodingError err = VP8_ENC_OK;
  VP8LBackwardRefs* refs;
  HuffmanTreeToken* tokens = NULL;
  HuffmanTreeCode huffman_codes[5] = { { 0, NULL, NULL } };
  const uint16_t histogram_symbols[1] = { 0 };    // only one tree, one symbol
  int cache_bits = 0;
  VP8LHistogramSet* histogram_image = NULL;
  HuffmanTree* const huff_tree = (HuffmanTree*)WebPSafeMalloc(
        3ULL * CODE_LENGTH_CODES, sizeof(*huff_tree));
  if (huff_tree == NULL) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  // Calculate backward references from ARGB image.
  if (!VP8LHashChainFill(hash_chain, quality, argb, width, height,
                         low_effort)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }
  refs = VP8LGetBackwardReferences(width, height, argb, quality, 0,
                                   kLZ77Standard | kLZ77RLE, &cache_bits,
                                   hash_chain, refs_tmp1, refs_tmp2);
  if (refs == NULL) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }
  histogram_image = VP8LAllocateHistogramSet(1, cache_bits);
  if (histogram_image == NULL) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }
  VP8LHistogramSetClear(histogram_image);

  // Build histogram image and symbols from backward references.
  VP8LHistogramStoreRefs(refs, histogram_image->histograms[0]);

  // Create Huffman bit lengths and codes for each histogram image.
  assert(histogram_image->size == 1);
  if (!GetHuffBitLengthsAndCodes(histogram_image, huffman_codes)) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  // No color cache, no Huffman image.
  VP8LPutBits(bw, 0, 1);

  // Find maximum number of symbols for the huffman tree-set.
  for (i = 0; i < 5; ++i) {
    HuffmanTreeCode* const codes = &huffman_codes[i];
    if (max_tokens < codes->num_symbols) {
      max_tokens = codes->num_symbols;
    }
  }

  tokens = (HuffmanTreeToken*)WebPSafeMalloc(max_tokens, sizeof(*tokens));
  if (tokens == NULL) {
    err = VP8_ENC_ERROR_OUT_OF_MEMORY;
    goto Error;
  }

  // Store Huffman codes.
  for (i = 0; i < 5; ++i) {
    HuffmanTreeCode* const codes = &huffman_codes[i];
    StoreHuffmanCode(bw, huff_tree, tokens, codes);
    ClearHuffmanTreeIfOnlyOneSymbol(codes);
  }

  // Store actual literals.
  err = StoreImageToBitMask(bw, width, 0, refs, histogram_symbols,
                            huffman_codes);

 Error:
  WebPSafeFree(tokens);
  WebPSafeFree(huff_tree);
  VP8LFreeHistogramSet(histogram_image);
  WebPSafeFree(huffman_codes[0].codes);
  return err;
}