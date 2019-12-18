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
typedef  int /*<<< orphan*/  Suite ;
typedef  int /*<<< orphan*/  SRunner ;

/* Variables and functions */
 int /*<<< orphan*/  CK_NORMAL ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  cmd_set_arguments (int,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * srunner_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srunner_free (int /*<<< orphan*/ *) ; 
 int srunner_ntests_failed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srunner_run_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * theme_parser_suite () ; 

int main ( int argc, char ** argv )
{
    cmd_set_arguments ( argc, argv );

    if ( setlocale ( LC_ALL, "C" ) == NULL ) {
        fprintf ( stderr, "Failed to set locale.\n" );
        return EXIT_FAILURE;
    }


    Suite *s;
    SRunner *sr;

    s = theme_parser_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}