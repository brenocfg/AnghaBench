#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct options_entry {int dummy; } ;
struct format_tree {TYPE_3__* s; int /*<<< orphan*/  tree; TYPE_2__* w; TYPE_1__* wp; } ;
struct format_entry {char* key; scalar_t__ t; char* value; int /*<<< orphan*/  (* cb ) (struct format_tree*,struct format_entry*) ;} ;
struct environ_entry {char* value; } ;
struct TYPE_6__ {int /*<<< orphan*/  environ; int /*<<< orphan*/  options; } ;
struct TYPE_5__ {int /*<<< orphan*/  options; } ;
struct TYPE_4__ {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int FORMAT_BASENAME ; 
 int FORMAT_DIRNAME ; 
 int FORMAT_QUOTE ; 
 int FORMAT_TIMESTRING ; 
 struct format_entry* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct format_entry*) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  ctime_r (scalar_t__*,char*) ; 
 char* dirname (char*) ; 
 struct environ_entry* environ_find (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  format_entry_tree ; 
 char* format_quote (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  global_s_options ; 
 int /*<<< orphan*/  global_w_options ; 
 struct options_entry* options_parse_get (int /*<<< orphan*/ ,char const*,int*,int /*<<< orphan*/ ) ; 
 char* options_tostring (struct options_entry*,int,int) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct format_tree*,struct format_entry*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,long long) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static char *
format_find(struct format_tree *ft, const char *key, int modifiers)
{
	struct format_entry	*fe, fe_find;
	struct environ_entry	*envent;
	static char		 s[64];
	struct options_entry	*o;
	int			 idx;
	char			*found, *saved;

	if (~modifiers & FORMAT_TIMESTRING) {
		o = options_parse_get(global_options, key, &idx, 0);
		if (o == NULL && ft->wp != NULL)
			o = options_parse_get(ft->wp->options, key, &idx, 0);
		if (o == NULL && ft->w != NULL)
			o = options_parse_get(ft->w->options, key, &idx, 0);
		if (o == NULL)
			o = options_parse_get(global_w_options, key, &idx, 0);
		if (o == NULL && ft->s != NULL)
			o = options_parse_get(ft->s->options, key, &idx, 0);
		if (o == NULL)
			o = options_parse_get(global_s_options, key, &idx, 0);
		if (o != NULL) {
			found = options_tostring(o, idx, 1);
			goto found;
		}
	}
	found = NULL;

	fe_find.key = (char *) key;
	fe = RB_FIND(format_entry_tree, &ft->tree, &fe_find);
	if (fe != NULL) {
		if (modifiers & FORMAT_TIMESTRING) {
			if (fe->t == 0)
				return (NULL);
			ctime_r(&fe->t, s);
			s[strcspn(s, "\n")] = '\0';
			found = xstrdup(s);
			goto found;
		}
		if (fe->t != 0) {
			xasprintf(&found, "%lld", (long long)fe->t);
			goto found;
		}
		if (fe->value == NULL && fe->cb != NULL) {
			fe->cb(ft, fe);
			if (fe->value == NULL)
				fe->value = xstrdup("");
		}
		found = xstrdup(fe->value);
		goto found;
	}

	if (~modifiers & FORMAT_TIMESTRING) {
		envent = NULL;
		if (ft->s != NULL)
			envent = environ_find(ft->s->environ, key);
		if (envent == NULL)
			envent = environ_find(global_environ, key);
		if (envent != NULL && envent->value != NULL) {
			found = xstrdup(envent->value);
			goto found;
		}
	}

	return (NULL);

found:
	if (found == NULL)
		return (NULL);
	if (modifiers & FORMAT_BASENAME) {
		saved = found;
		found = xstrdup(basename(saved));
		free(saved);
	}
	if (modifiers & FORMAT_DIRNAME) {
		saved = found;
		found = xstrdup(dirname(saved));
		free(saved);
	}
	if (modifiers & FORMAT_QUOTE) {
		saved = found;
		found = xstrdup(format_quote(saved));
		free(saved);
	}
	return (found);
}