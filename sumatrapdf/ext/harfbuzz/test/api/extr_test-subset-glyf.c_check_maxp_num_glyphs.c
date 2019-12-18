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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  hb_face_t ;
typedef  int /*<<< orphan*/  hb_blob_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_TAG (char,char,char,char) ; 
 int /*<<< orphan*/  check_maxp_field (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hb_blob_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_blob_get_data (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/ * hb_face_reference_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_maxp_num_glyphs (hb_face_t *face, uint16_t expected_num_glyphs, bool hints)
{
  hb_blob_t *maxp_blob = hb_face_reference_table (face, HB_TAG ('m','a','x', 'p'));

  unsigned int maxp_len;
  uint8_t *raw_maxp = (uint8_t *) hb_blob_get_data(maxp_blob, &maxp_len);

  check_maxp_field (raw_maxp, 4, expected_num_glyphs); // numGlyphs
  if (!hints)
  {
    check_maxp_field (raw_maxp, 14, 1); // maxZones
    check_maxp_field (raw_maxp, 16, 0); // maxTwilightPoints
    check_maxp_field (raw_maxp, 18, 0); // maxStorage
    check_maxp_field (raw_maxp, 20, 0); // maxFunctionDefs
    check_maxp_field (raw_maxp, 22, 0); // maxInstructionDefs
    check_maxp_field (raw_maxp, 24, 0); // maxStackElements
    check_maxp_field (raw_maxp, 26, 0); // maxSizeOfInstructions
  }

  hb_blob_destroy (maxp_blob);
}