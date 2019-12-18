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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
struct TYPE_3__ {struct TYPE_3__* next; int /*<<< orphan*/  guest_ok; int /*<<< orphan*/  comment; int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ smb_share_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  file_path ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int PATH_MAX ; 
 int SA_NO_MEMORY ; 
 int SA_OK ; 
 int SA_SYSTEM_ERR ; 
 char* SHARE_DIR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 TYPE_1__* smb_shares ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
smb_retrieve_shares(void)
{
	int rc = SA_OK;
	char file_path[PATH_MAX], line[512], *token, *key, *value;
	char *dup_value = NULL, *path = NULL, *comment = NULL, *name = NULL;
	char *guest_ok = NULL;
	DIR *shares_dir;
	FILE *share_file_fp = NULL;
	struct dirent *directory;
	struct stat eStat;
	smb_share_t *shares, *new_shares = NULL;

	/* opendir(), stat() */
	shares_dir = opendir(SHARE_DIR);
	if (shares_dir == NULL)
		return (SA_SYSTEM_ERR);

	/* Go through the directory, looking for shares */
	while ((directory = readdir(shares_dir))) {
		if (directory->d_name[0] == '.')
			continue;

		snprintf(file_path, sizeof (file_path),
		    "%s/%s", SHARE_DIR, directory->d_name);

		if (stat(file_path, &eStat) == -1) {
			rc = SA_SYSTEM_ERR;
			goto out;
		}

		if (!S_ISREG(eStat.st_mode))
			continue;

		if ((share_file_fp = fopen(file_path, "r")) == NULL) {
			rc = SA_SYSTEM_ERR;
			goto out;
		}

		name = strdup(directory->d_name);
		if (name == NULL) {
			rc = SA_NO_MEMORY;
			goto out;
		}

		while (fgets(line, sizeof (line), share_file_fp)) {
			if (line[0] == '#')
				continue;

			/* Trim trailing new-line character(s). */
			while (line[strlen(line) - 1] == '\r' ||
			    line[strlen(line) - 1] == '\n')
				line[strlen(line) - 1] = '\0';

			/* Split the line in two, separated by '=' */
			token = strchr(line, '=');
			if (token == NULL)
				continue;

			key = line;
			value = token + 1;
			*token = '\0';

			dup_value = strdup(value);
			if (dup_value == NULL) {
				rc = SA_NO_MEMORY;
				goto out;
			}

			if (strcmp(key, "path") == 0) {
				free(path);
				path = dup_value;
			} else if (strcmp(key, "comment") == 0) {
				free(comment);
				comment = dup_value;
			} else if (strcmp(key, "guest_ok") == 0) {
				free(guest_ok);
				guest_ok = dup_value;
			} else
				free(dup_value);

			dup_value = NULL;

			if (path == NULL || comment == NULL || guest_ok == NULL)
				continue; /* Incomplete share definition */
			else {
				shares = (smb_share_t *)
				    malloc(sizeof (smb_share_t));
				if (shares == NULL) {
					rc = SA_NO_MEMORY;
					goto out;
				}

				(void) strlcpy(shares->name, name,
				    sizeof (shares->name));

				(void) strlcpy(shares->path, path,
				    sizeof (shares->path));

				(void) strlcpy(shares->comment, comment,
				    sizeof (shares->comment));

				shares->guest_ok = atoi(guest_ok);

				shares->next = new_shares;
				new_shares = shares;

				free(path);
				free(comment);
				free(guest_ok);

				path = NULL;
				comment = NULL;
				guest_ok = NULL;
			}
		}

out:
		if (share_file_fp != NULL) {
			fclose(share_file_fp);
			share_file_fp = NULL;
		}

		free(name);
		free(path);
		free(comment);
		free(guest_ok);

		name = NULL;
		path = NULL;
		comment = NULL;
		guest_ok = NULL;
	}
	closedir(shares_dir);

	smb_shares = new_shares;

	return (rc);
}