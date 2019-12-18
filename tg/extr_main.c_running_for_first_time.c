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
 int /*<<< orphan*/  CONFIG_DIRECTORY_MODE ; 
 int /*<<< orphan*/  CONFIG_FILE ; 
 int /*<<< orphan*/  DEFAULT_CONFIG_CONTENTS ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  R_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_type_sizes () ; 
 int /*<<< orphan*/  close (int) ; 
 char* config_directory ; 
 char* config_filename ; 
 int /*<<< orphan*/  disable_output ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* get_config_directory () ; 
 char* make_full_path (char*) ; 
 int /*<<< orphan*/  mkdir (char*,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ str_empty (char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasprintf (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfree_str (char*) ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void running_for_first_time (void) {
  check_type_sizes ();
  if (!str_empty (config_filename)) {
    return; // Do not create custom config file
  }
  if (str_empty (config_directory)) {
    config_directory = get_config_directory ();
  }
  tasprintf (&config_filename, "%s/%s", config_directory, CONFIG_FILE);
  config_filename = make_full_path (config_filename);
  if (!disable_output) {
    printf ("I: config dir=[%s]\n", config_directory);
  }
  // printf ("I: config file=[%s]\n", config_filename);

  int config_file_fd;
  //char *config_directory = get_config_directory ();
  //char *downloads_directory = get_downloads_directory ();

  if (!mkdir (config_directory, CONFIG_DIRECTORY_MODE)) {
    if (!disable_output) {
      printf ("[%s] created\n", config_directory);
    }
  }

  tfree_str (config_directory);
  config_directory = NULL;
  // see if config file is there
  if (access (config_filename, R_OK) != 0) {
    // config file missing, so touch it
    config_file_fd = open (config_filename, O_CREAT | O_RDWR, 0600);
    if (config_file_fd == -1)  {
      perror ("open[config_file]");
      printf ("I: config_file=[%s]\n", config_filename);
      exit (EXIT_FAILURE);
    }
    if (write (config_file_fd, DEFAULT_CONFIG_CONTENTS, strlen (DEFAULT_CONFIG_CONTENTS)) <= 0) {
      perror ("write[config_file]");
      exit (EXIT_FAILURE);
    }
    close (config_file_fd);
  }
}