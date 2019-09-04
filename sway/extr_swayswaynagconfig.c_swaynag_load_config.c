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
struct swaynag_type {int dummy; } ;
struct swaynag {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* calloc (int,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct swaynag_type*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int swaynag_parse_options (int,char**,struct swaynag*,int /*<<< orphan*/ *,struct swaynag_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct swaynag_type* swaynag_type_get (int /*<<< orphan*/ *,char*) ; 
 struct swaynag_type* swaynag_type_new (char*) ; 

int swaynag_load_config(char *path, struct swaynag *swaynag, list_t *types) {
	FILE *config = fopen(path, "r");
	if (!config) {
		fprintf(stderr, "Failed to read config. Running without it.\n");
		return 0;
	}

	struct swaynag_type *type = swaynag_type_new("<config>");
	list_add(types, type);

	char *line = NULL;
	size_t line_size = 0;
	ssize_t nread;
	int line_number = 0;
	int result = 0;
	while ((nread = getline(&line, &line_size, config)) != -1) {
		line_number++;
		if (!*line || line[0] == '\n' || line[0] == '#') {
			continue;
		}

		if (line[nread - 1] == '\n') {
			line[nread - 1] = '\0';
		}

		if (line[0] == '[') {
			char *close = strchr(line, ']');
			if (!close) {
				fprintf(stderr, "Closing bracket not found on line %d\n",
						line_number);
				result = 1;
				break;
			}
			char *name = calloc(1, close - line);
			strncat(name, line + 1, close - line - 1);
			type = swaynag_type_get(types, name);
			if (!type) {
				type = swaynag_type_new(name);
				list_add(types, type);
			}
			free(name);
		} else {
			char *flag = malloc(sizeof(char) * (nread + 3));
			sprintf(flag, "--%s", line);
			char *argv[] = {"swaynag", flag};
			result = swaynag_parse_options(2, argv, swaynag, types, type,
					NULL, NULL);
			free(flag);
			if (result != 0) {
				break;
			}
		}
	}
	free(line);
	fclose(config);
	return result;
}