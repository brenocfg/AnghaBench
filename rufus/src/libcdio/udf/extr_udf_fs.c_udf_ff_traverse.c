#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ b_dir; int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ udf_dirent_t ;

/* Variables and functions */
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strtok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_PATH_DELIMITERS ; 
 int /*<<< orphan*/  udf_dirent_free (TYPE_1__*) ; 
 TYPE_1__* udf_opendir (TYPE_1__*) ; 
 TYPE_1__* udf_readdir (TYPE_1__*) ; 

__attribute__((used)) static
udf_dirent_t *
udf_ff_traverse(udf_dirent_t *p_udf_dirent, char *psz_token)
{
  while ((p_udf_dirent = udf_readdir(p_udf_dirent))) {
    if (strcmp(psz_token, p_udf_dirent->psz_name) == 0) {
      char *next_tok = strtok(NULL, udf_PATH_DELIMITERS);

      if (!next_tok)
	return p_udf_dirent; /* found */
      else if (p_udf_dirent->b_dir) {
	udf_dirent_t * p_udf_dirent_next = udf_opendir(p_udf_dirent);

	if (p_udf_dirent_next) {
	  /* free p_udf_dirent to avoid leaking memory. */
	  udf_dirent_free(p_udf_dirent);

	  /* previous p_udf_dirent_next is freed by udf_ff_traverse. */
	  p_udf_dirent_next = udf_ff_traverse(p_udf_dirent_next, next_tok);

	  return p_udf_dirent_next;
	}
      }
    }
  }

  return NULL;
}