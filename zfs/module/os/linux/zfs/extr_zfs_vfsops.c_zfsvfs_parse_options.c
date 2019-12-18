#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_t ;
struct TYPE_4__ {int /*<<< orphan*/ * from; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ substring_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MAX_OPT_ARGS ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 char* kmem_strdup (char*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* strsep (char**,char*) ; 
 int zfsvfs_parse_option (char*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsvfs_vfs_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpl_tokens ; 

__attribute__((used)) static int
zfsvfs_parse_options(char *mntopts, vfs_t **vfsp)
{
	vfs_t *tmp_vfsp;
	int error;

	tmp_vfsp = kmem_zalloc(sizeof (vfs_t), KM_SLEEP);

	if (mntopts != NULL) {
		substring_t args[MAX_OPT_ARGS];
		char *tmp_mntopts, *p, *t;
		int token;

		tmp_mntopts = t = kmem_strdup(mntopts);
		if (tmp_mntopts == NULL)
			return (SET_ERROR(ENOMEM));

		while ((p = strsep(&t, ",")) != NULL) {
			if (!*p)
				continue;

			args[0].to = args[0].from = NULL;
			token = match_token(p, zpl_tokens, args);
			error = zfsvfs_parse_option(p, token, args, tmp_vfsp);
			if (error) {
				kmem_strfree(tmp_mntopts);
				zfsvfs_vfs_free(tmp_vfsp);
				return (error);
			}
		}

		kmem_strfree(tmp_mntopts);
	}

	*vfsp = tmp_vfsp;

	return (0);
}