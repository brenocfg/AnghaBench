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
typedef  int /*<<< orphan*/  hb_unicode_funcs_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  gconstpointer ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ fixture_t ;

/* Variables and functions */
 scalar_t__ HB_BUFFER_FLAGS_DEFAULT ; 
 scalar_t__ HB_BUFFER_FLAG_BOT ; 
 unsigned int HB_BUFFER_REPLACEMENT_CODEPOINT_DEFAULT ; 
 scalar_t__ HB_DIRECTION_INVALID ; 
 scalar_t__ HB_DIRECTION_RTL ; 
 scalar_t__ HB_SCRIPT_ARABIC ; 
 scalar_t__ HB_SCRIPT_INVALID ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  hb_buffer_clear_contents (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_buffer_get_direction (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_buffer_get_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_buffer_get_language (int /*<<< orphan*/ *) ; 
 unsigned int hb_buffer_get_replacement_codepoint (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_buffer_get_script (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_buffer_get_unicode_funcs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_set_direction (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hb_buffer_set_flags (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hb_buffer_set_language (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_buffer_set_replacement_codepoint (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  hb_buffer_set_script (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hb_buffer_set_unicode_funcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_language_from_string (char*,int) ; 
 int /*<<< orphan*/ * hb_unicode_funcs_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_unicode_funcs_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_unicode_funcs_get_default () ; 

__attribute__((used)) static void
test_buffer_properties (fixture_t *fixture, gconstpointer user_data)
{
  hb_buffer_t *b = fixture->buffer;
  hb_unicode_funcs_t *ufuncs;

  /* test default properties */

  g_assert (hb_buffer_get_unicode_funcs (b) == hb_unicode_funcs_get_default ());
  g_assert (hb_buffer_get_direction (b) == HB_DIRECTION_INVALID);
  g_assert (hb_buffer_get_script (b) == HB_SCRIPT_INVALID);
  g_assert (hb_buffer_get_language (b) == NULL);


  /* test property changes are retained */
  ufuncs = hb_unicode_funcs_create (NULL);
  hb_buffer_set_unicode_funcs (b, ufuncs);
  hb_unicode_funcs_destroy (ufuncs);
  g_assert (hb_buffer_get_unicode_funcs (b) == ufuncs);

  hb_buffer_set_direction (b, HB_DIRECTION_RTL);
  g_assert (hb_buffer_get_direction (b) == HB_DIRECTION_RTL);

  hb_buffer_set_script (b, HB_SCRIPT_ARABIC);
  g_assert (hb_buffer_get_script (b) == HB_SCRIPT_ARABIC);

  hb_buffer_set_language (b, hb_language_from_string ("fa", -1));
  g_assert (hb_buffer_get_language (b) == hb_language_from_string ("Fa", -1));

  hb_buffer_set_flags (b, HB_BUFFER_FLAG_BOT);
  g_assert (hb_buffer_get_flags (b) == HB_BUFFER_FLAG_BOT);

  hb_buffer_set_replacement_codepoint (b, (unsigned int) -1);
  g_assert (hb_buffer_get_replacement_codepoint (b) == (unsigned int) -1);


  /* test clear_contents clears all these properties: */

  hb_buffer_clear_contents (b);

  g_assert (hb_buffer_get_unicode_funcs (b) == ufuncs);
  g_assert (hb_buffer_get_direction (b) == HB_DIRECTION_INVALID);
  g_assert (hb_buffer_get_script (b) == HB_SCRIPT_INVALID);
  g_assert (hb_buffer_get_language (b) == NULL);

  /* but not these: */

  g_assert (hb_buffer_get_flags (b) != HB_BUFFER_FLAGS_DEFAULT);
  g_assert (hb_buffer_get_replacement_codepoint (b) != HB_BUFFER_REPLACEMENT_CODEPOINT_DEFAULT);


  /* test reset clears all properties */

  hb_buffer_set_direction (b, HB_DIRECTION_RTL);
  g_assert (hb_buffer_get_direction (b) == HB_DIRECTION_RTL);

  hb_buffer_set_script (b, HB_SCRIPT_ARABIC);
  g_assert (hb_buffer_get_script (b) == HB_SCRIPT_ARABIC);

  hb_buffer_set_language (b, hb_language_from_string ("fa", -1));
  g_assert (hb_buffer_get_language (b) == hb_language_from_string ("Fa", -1));

  hb_buffer_set_flags (b, HB_BUFFER_FLAG_BOT);
  g_assert (hb_buffer_get_flags (b) == HB_BUFFER_FLAG_BOT);

  hb_buffer_set_replacement_codepoint (b, (unsigned int) -1);
  g_assert (hb_buffer_get_replacement_codepoint (b) == (unsigned int) -1);

  hb_buffer_reset (b);

  g_assert (hb_buffer_get_unicode_funcs (b) == hb_unicode_funcs_get_default ());
  g_assert (hb_buffer_get_direction (b) == HB_DIRECTION_INVALID);
  g_assert (hb_buffer_get_script (b) == HB_SCRIPT_INVALID);
  g_assert (hb_buffer_get_language (b) == NULL);
  g_assert (hb_buffer_get_flags (b) == HB_BUFFER_FLAGS_DEFAULT);
  g_assert (hb_buffer_get_replacement_codepoint (b) == HB_BUFFER_REPLACEMENT_CODEPOINT_DEFAULT);
}