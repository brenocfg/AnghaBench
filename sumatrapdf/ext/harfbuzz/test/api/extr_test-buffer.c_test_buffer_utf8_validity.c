#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int max_len; scalar_t__ offset; scalar_t__ valid; int /*<<< orphan*/  utf8; } ;
typedef  TYPE_1__ utf8_validity_test_t ;
struct TYPE_7__ {scalar_t__ codepoint; scalar_t__ cluster; } ;
typedef  TYPE_2__ hb_glyph_info_t ;
typedef  scalar_t__ hb_codepoint_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 unsigned int G_N_ELEMENTS (TYPE_1__*) ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strescape (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_test_message (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  hb_buffer_add_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hb_buffer_clear_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_buffer_create () ; 
 int /*<<< orphan*/  hb_buffer_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* hb_buffer_get_glyph_infos (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  hb_buffer_set_replacement_codepoint (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 
 TYPE_1__* utf8_validity_tests ; 

__attribute__((used)) static void
test_buffer_utf8_validity (void)
{
  hb_buffer_t *b;
  unsigned int i;

  b = hb_buffer_create ();
  hb_buffer_set_replacement_codepoint (b, (hb_codepoint_t) -1);

  for (i = 0; i < G_N_ELEMENTS (utf8_validity_tests); i++)
  {
    const utf8_validity_test_t *test = &utf8_validity_tests[i];
    unsigned int text_bytes, segment_bytes, j, len;
    hb_glyph_info_t *glyphs;
    char *escaped;

    escaped = g_strescape (test->utf8, NULL);
    g_test_message ("UTF-8 test #%d: %s", i, escaped);
    g_free (escaped);

    text_bytes = strlen (test->utf8);
    if (test->max_len == -1)
      segment_bytes = text_bytes;
    else
      segment_bytes = test->max_len;

    hb_buffer_clear_contents (b);
    hb_buffer_add_utf8 (b, test->utf8, text_bytes,  0, segment_bytes);

    glyphs = hb_buffer_get_glyph_infos (b, &len);
    for (j = 0; j < len; j++)
      if (glyphs[j].codepoint == (hb_codepoint_t) -1)
	break;

    g_assert (test->valid ? j == len : j < len);
    if (!test->valid)
      g_assert (glyphs[j].cluster == test->offset);
  }

  hb_buffer_destroy (b);
}