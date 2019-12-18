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
 void* GINT_TO_POINTER (unsigned int) ; 
 unsigned int G_N_ELEMENTS (char**) ; 
 char** blob_names ; 
 int /*<<< orphan*/  fixture ; 
 int /*<<< orphan*/  hb_test_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_add_fixture_flavor (int /*<<< orphan*/ ,void const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_test_init (int*,char***) ; 
 int hb_test_run () ; 
 int /*<<< orphan*/  test_blob ; 
 int /*<<< orphan*/  test_blob_empty ; 
 int /*<<< orphan*/  test_blob_subblob ; 

int
main (int argc, char **argv)
{
  unsigned int i;

  hb_test_init (&argc, &argv);

  hb_test_add (test_blob_empty);

  for (i = 0; i < G_N_ELEMENTS (blob_names); i++)
  {
    const void *blob_type = GINT_TO_POINTER (i);
    const char *blob_name = blob_names[i];

    hb_test_add_fixture_flavor (fixture, blob_type, blob_name, test_blob);
    hb_test_add_fixture_flavor (fixture, blob_type, blob_name, test_blob_subblob);
  }

  /*
   * create_sub_blob
   */

  return hb_test_run ();
}