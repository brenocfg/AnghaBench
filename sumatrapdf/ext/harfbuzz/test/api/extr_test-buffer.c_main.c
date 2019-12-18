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

/* Variables and functions */
 unsigned int BUFFER_EMPTY ; 
 unsigned int BUFFER_NUM_TYPES ; 
 void* GINT_TO_POINTER (unsigned int) ; 
 char** buffer_names ; 
 int /*<<< orphan*/  fixture ; 
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_add_fixture (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_add_fixture_flavor (int /*<<< orphan*/ ,void const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  test_buffer_allocation ; 
 int /*<<< orphan*/  test_buffer_contents ; 
 int /*<<< orphan*/  test_buffer_empty ; 
 int /*<<< orphan*/  test_buffer_positions ; 
 int /*<<< orphan*/  test_buffer_properties ; 
 int /*<<< orphan*/  test_buffer_utf16_conversion ; 
 int /*<<< orphan*/  test_buffer_utf32_conversion ; 
 int /*<<< orphan*/  test_buffer_utf8_conversion ; 
 int /*<<< orphan*/  test_buffer_utf8_validity ; 

int
main (int argc, char **argv)
{
  unsigned int i;

  hb_test_init (&argc, &argv);

  for (i = 0; i < BUFFER_NUM_TYPES; i++)
  {
    const void *buffer_type = GINT_TO_POINTER (i);
    const char *buffer_name = buffer_names[i];

    hb_test_add_fixture_flavor (fixture, buffer_type, buffer_name, test_buffer_properties);
    hb_test_add_fixture_flavor (fixture, buffer_type, buffer_name, test_buffer_contents);
    hb_test_add_fixture_flavor (fixture, buffer_type, buffer_name, test_buffer_positions);
  }

  hb_test_add_fixture (fixture, GINT_TO_POINTER (BUFFER_EMPTY), test_buffer_allocation);

  hb_test_add (test_buffer_utf8_conversion);
  hb_test_add (test_buffer_utf8_validity);
  hb_test_add (test_buffer_utf16_conversion);
  hb_test_add (test_buffer_utf32_conversion);
  hb_test_add (test_buffer_empty);

  return hb_test_run();
}