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
typedef  int /*<<< orphan*/  hb_unicode_funcs_t ;
typedef  int hb_codepoint_t ;
typedef  int gunichar ;
typedef  scalar_t__ gconstpointer ;

/* Variables and functions */
 int HB_UNICODE_MAX_DECOMPOSITION_LEN ; 
 int /*<<< orphan*/  g_assert (int) ; 
 scalar_t__ hb_unicode_compose (int /*<<< orphan*/ *,int,int,int*) ; 
 scalar_t__ hb_unicode_decompose (int /*<<< orphan*/ *,int,int*,int*) ; 
 int hb_unicode_decompose_compatibility (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void
test_unicode_normalization (gconstpointer user_data)
{
  hb_unicode_funcs_t *uf = (hb_unicode_funcs_t *) user_data;
  gunichar a, b, ab;
  hb_codepoint_t decomposed[HB_UNICODE_MAX_DECOMPOSITION_LEN];


  /* Test compose() */

  /* Not composable */
  g_assert (!hb_unicode_compose (uf, 0x0041, 0x0042, &ab) && ab == 0);
  g_assert (!hb_unicode_compose (uf, 0x0041, 0, &ab) && ab == 0);
  g_assert (!hb_unicode_compose (uf, 0x0066, 0x0069, &ab) && ab == 0);

  /* Singletons should not compose */
  g_assert (!hb_unicode_compose (uf, 0x212B, 0, &ab) && ab == 0);
  g_assert (!hb_unicode_compose (uf, 0x00C5, 0, &ab) && ab == 0);
  g_assert (!hb_unicode_compose (uf, 0x2126, 0, &ab) && ab == 0);
  g_assert (!hb_unicode_compose (uf, 0x03A9, 0, &ab) && ab == 0);

  /* Non-starter pairs should not compose */
  g_assert (!hb_unicode_compose (uf, 0x0308, 0x0301, &ab) && ab == 0); /* !0x0344 */
  g_assert (!hb_unicode_compose (uf, 0x0F71, 0x0F72, &ab) && ab == 0); /* !0x0F73 */

  /* Pairs */
  g_assert (hb_unicode_compose (uf, 0x0041, 0x030A, &ab) && ab == 0x00C5);
  g_assert (hb_unicode_compose (uf, 0x006F, 0x0302, &ab) && ab == 0x00F4);
  g_assert (hb_unicode_compose (uf, 0x1E63, 0x0307, &ab) && ab == 0x1E69);
  g_assert (hb_unicode_compose (uf, 0x0073, 0x0323, &ab) && ab == 0x1E63);
  g_assert (hb_unicode_compose (uf, 0x0064, 0x0307, &ab) && ab == 0x1E0B);
  g_assert (hb_unicode_compose (uf, 0x0064, 0x0323, &ab) && ab == 0x1E0D);

  /* Hangul */
  g_assert (hb_unicode_compose (uf, 0xD4CC, 0x11B6, &ab) && ab == 0xD4DB);
  g_assert (hb_unicode_compose (uf, 0x1111, 0x1171, &ab) && ab == 0xD4CC);
  g_assert (hb_unicode_compose (uf, 0xCE20, 0x11B8, &ab) && ab == 0xCE31);
  g_assert (hb_unicode_compose (uf, 0x110E, 0x1173, &ab) && ab == 0xCE20);


  /* Test decompose() */

  /* Not decomposable */
  g_assert (!hb_unicode_decompose (uf, 0x0041, &a, &b) && a == 0x0041 && b == 0);
  g_assert (!hb_unicode_decompose (uf, 0xFB01, &a, &b) && a == 0xFB01 && b == 0);
  g_assert (!hb_unicode_decompose (uf, 0x1F1EF, &a, &b) && a == 0x1F1EF && b == 0);

  /* Singletons */
  g_assert (hb_unicode_decompose (uf, 0x212B, &a, &b) && a == 0x00C5 && b == 0);
  g_assert (hb_unicode_decompose (uf, 0x2126, &a, &b) && a == 0x03A9 && b == 0);

  /* Non-starter pairs decompose, but not compose */
  g_assert (hb_unicode_decompose (uf, 0x0344, &a, &b) && a == 0x0308 && b == 0x0301);
  g_assert (hb_unicode_decompose (uf, 0x0F73, &a, &b) && a == 0x0F71 && b == 0x0F72);

  /* Pairs */
  g_assert (hb_unicode_decompose (uf, 0x00C5, &a, &b) && a == 0x0041 && b == 0x030A);
  g_assert (hb_unicode_decompose (uf, 0x00F4, &a, &b) && a == 0x006F && b == 0x0302);
  g_assert (hb_unicode_decompose (uf, 0x1E69, &a, &b) && a == 0x1E63 && b == 0x0307);
  g_assert (hb_unicode_decompose (uf, 0x1E63, &a, &b) && a == 0x0073 && b == 0x0323);
  g_assert (hb_unicode_decompose (uf, 0x1E0B, &a, &b) && a == 0x0064 && b == 0x0307);
  g_assert (hb_unicode_decompose (uf, 0x1E0D, &a, &b) && a == 0x0064 && b == 0x0323);

  /* Hangul */
  g_assert (hb_unicode_decompose (uf, 0xD4DB, &a, &b) && a == 0xD4CC && b == 0x11B6);
  g_assert (hb_unicode_decompose (uf, 0xD4CC, &a, &b) && a == 0x1111 && b == 0x1171);
  g_assert (hb_unicode_decompose (uf, 0xCE31, &a, &b) && a == 0xCE20 && b == 0x11B8);
  g_assert (hb_unicode_decompose (uf, 0xCE20, &a, &b) && a == 0x110E && b == 0x1173);


  /* Test decompose_compatibility() */

  /* Not decomposable */
  g_assert (hb_unicode_decompose_compatibility (uf, 0x0041, decomposed) == 0);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x1F632, decomposed) == 0);

  /* Singletons */
  g_assert (hb_unicode_decompose_compatibility (uf, 0x00B5, decomposed) == 1 && decomposed[0] == 0x03BC);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x03D6, decomposed) == 1 && decomposed[0] == 0x03C0);

  /* Arabic compatibility */
  g_assert (hb_unicode_decompose_compatibility (uf, 0xFB54, decomposed) == 1 && decomposed[0] == 0x067B);

  /* Longest decomposition ever */
  g_assert (18 <= HB_UNICODE_MAX_DECOMPOSITION_LEN);
  g_assert (hb_unicode_decompose_compatibility (uf, 0xFDFA, decomposed) == 18 && decomposed[17] == 0x0645);

  /* Note: we deliberately don't test characters that have canonical decompositions but no
   * compatibility decomposition against the decompose_compatibility() function as that we
   * leave up to implementations (for now). */

  /* Spaces */
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2002, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2003, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2004, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2005, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2006, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2008, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2009, decomposed) == 1 && decomposed[0] == 0x0020);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x200A, decomposed) == 1 && decomposed[0] == 0x0020);

  /* Pairs */
  g_assert (hb_unicode_decompose_compatibility (uf, 0x0587, decomposed) == 2 &&
            decomposed[0] == 0x0565 && decomposed[1] == 0x0582);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2017, decomposed) == 2 &&
            decomposed[0] == 0x0020 && decomposed[1] == 0x0333);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2025, decomposed) == 2 &&
            decomposed[0] == 0x002E && decomposed[1] == 0x002E);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2033, decomposed) == 2 &&
            decomposed[0] == 0x2032 && decomposed[1] == 0x2032);

  /* Triples */
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2026, decomposed) == 3 &&
            decomposed[0] == 0x002E && decomposed[1] == 0x002E && decomposed[2] == 0x002E);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x2034, decomposed) == 3 &&
            decomposed[0] == 0x2032 && decomposed[1] == 0x2032 && decomposed[2] == 0x2032);
  g_assert (hb_unicode_decompose_compatibility (uf, 0x213B, decomposed) == 3 &&
            decomposed[0] == 0x0046 && decomposed[1] == 0x0041 && decomposed[2] == 0x0058);
}