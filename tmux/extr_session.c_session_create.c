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
struct termios {int dummy; } ;
struct session {int references; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  id; int /*<<< orphan*/ * name; int /*<<< orphan*/ * tio; struct options* options; struct environ* environ; int /*<<< orphan*/  windows; int /*<<< orphan*/  lastw; int /*<<< orphan*/ * curw; void* cwd; scalar_t__ flags; } ;
struct options {int dummy; } ;
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct session*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct termios*,int) ; 
 int /*<<< orphan*/  next_session_id ; 
 int /*<<< orphan*/  session_update_activity (struct session*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sessions ; 
 int /*<<< orphan*/  status_update_cache (struct session*) ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ **,char*,char const*,...) ; 
 struct session* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xmalloc (int) ; 
 void* xstrdup (char const*) ; 

struct session *
session_create(const char *prefix, const char *name, const char *cwd,
    struct environ *env, struct options *oo, struct termios *tio)
{
	struct session	*s;

	s = xcalloc(1, sizeof *s);
	s->references = 1;
	s->flags = 0;

	s->cwd = xstrdup(cwd);

	s->curw = NULL;
	TAILQ_INIT(&s->lastw);
	RB_INIT(&s->windows);

	s->environ = env;
	s->options = oo;

	status_update_cache(s);

	s->tio = NULL;
	if (tio != NULL) {
		s->tio = xmalloc(sizeof *s->tio);
		memcpy(s->tio, tio, sizeof *s->tio);
	}

	if (name != NULL) {
		s->name = xstrdup(name);
		s->id = next_session_id++;
	} else {
		s->name = NULL;
		do {
			s->id = next_session_id++;
			free(s->name);
			if (prefix != NULL)
				xasprintf(&s->name, "%s-%u", prefix, s->id);
			else
				xasprintf(&s->name, "%u", s->id);
		} while (RB_FIND(sessions, &sessions, s) != NULL);
	}
	RB_INSERT(sessions, &sessions, s);

	log_debug("new session %s $%u", s->name, s->id);

	if (gettimeofday(&s->creation_time, NULL) != 0)
		fatal("gettimeofday failed");
	session_update_activity(s, &s->creation_time);

	return (s);
}