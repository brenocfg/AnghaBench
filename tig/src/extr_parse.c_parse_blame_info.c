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
struct blame_commit {void* filename; void* parent_filename; int /*<<< orphan*/  parent_id; int /*<<< orphan*/  title; int /*<<< orphan*/  time; int /*<<< orphan*/  author; } ;

/* Variables and functions */
 scalar_t__ SIZEOF_REV ; 
 int /*<<< orphan*/  SIZEOF_STR ; 
 int /*<<< orphan*/  get_author (char*,char*) ; 
 void* get_path (char*) ; 
 scalar_t__ match_blame_header (char*,char**) ; 
 int /*<<< orphan*/  parse_timesec (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  parse_timezone (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string_copy_rev (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_ncopy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  string_ncopy_do (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

bool
parse_blame_info(struct blame_commit *commit, char author[SIZEOF_STR], char *line)
{
	if (match_blame_header("author ", &line)) {
		string_ncopy_do(author, SIZEOF_STR, line, strlen(line));

	} else if (match_blame_header("author-mail ", &line)) {
		char *end = strchr(line, '>');

		if (end)
			*end = 0;
		if (*line == '<')
			line++;
		commit->author = get_author(author, line);
		author[0] = 0;

	} else if (match_blame_header("author-time ", &line)) {
		parse_timesec(&commit->time, line);

	} else if (match_blame_header("author-tz ", &line)) {
		parse_timezone(&commit->time, line);

	} else if (match_blame_header("summary ", &line)) {
		string_ncopy(commit->title, line, strlen(line));

	} else if (match_blame_header("previous ", &line)) {
		if (strlen(line) <= SIZEOF_REV)
			return false;
		string_copy_rev(commit->parent_id, line);
		line += SIZEOF_REV;
		commit->parent_filename = get_path(line);
		if (!commit->parent_filename)
			return true;

	} else if (match_blame_header("filename ", &line)) {
		commit->filename = get_path(line);
		return true;
	}

	return false;
}