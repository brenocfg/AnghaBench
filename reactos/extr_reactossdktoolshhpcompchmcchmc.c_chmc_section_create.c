#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct chmcSection {char* name; char* filename; scalar_t__ fd; scalar_t__ mark_count; int /*<<< orphan*/  mark_list; int /*<<< orphan*/  control_data; int /*<<< orphan*/  reset_table_header; int /*<<< orphan*/  len; scalar_t__ offset; } ;
struct chmcFile {TYPE_1__* config; } ;
struct TYPE_2__ {char* tmpdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct chmcSection* calloc (int,int) ; 
 int /*<<< orphan*/  chmc_control_data_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chmc_reset_table_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chmcerr_msg (char*,char const*) ; 
 int /*<<< orphan*/  chmcerr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (struct chmcSection*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ mkstemps (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

struct chmcSection *chmc_section_create(struct chmcFile *chm,
                                        const char *name)
{
	struct chmcSection *section;

	assert(name);

	section = calloc(1, sizeof(struct chmcSection));
	if (section) {
		const char *tmpdir;
		int len;

		len = strlen(name);
		memcpy(section->name, name, len + 1);
		section->offset = 0;
		section->len = 0;

		tmpdir = NULL;
		if (chm->config != NULL)
			tmpdir = chm->config->tmpdir;
		if (tmpdir == NULL)
			tmpdir = "/tmp/";

		len = strlen(tmpdir);
		if (len >= PATH_MAX - 12) {
			chmcerr_set(errno, strerror(errno));
			chmcerr_msg("tmpdir too long: '%s'", tmpdir);
			goto fail;
		}

		strcat(section->filename, tmpdir);
		if (section->filename[len - 1] != '/')
			strcat(section->filename, "/");

		if (strcmp("MSCompressed", name) == 0)
			strcat(section->filename, "chmcCXXXXXX");
		else
			strcat(section->filename, "chmcUXXXXXX");

		section->fd = mkstemps(section->filename, 0);
		fprintf(stderr, "temp file: %s\n", section->filename);
		if (section->fd < 0) {
			chmcerr_set(errno, strerror(errno));
			chmcerr_msg("creat() file '%s'", section->filename);
			goto fail;
		}
		else if (strcmp(section->name, "MSCompressed") == 0) {
			chmc_reset_table_init(&section->reset_table_header);
			chmc_control_data_init(&section->control_data);
			INIT_LIST_HEAD(&section->mark_list);
			section->mark_count = 0;
		}
	} else {
		chmcerr_set(errno, strerror(errno));
		chmcerr_msg("section '%s' allocation failed", name);
	}

	return section;

 fail:
	free(section);
	return NULL;
}