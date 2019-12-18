#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  prog; scalar_t__ last; } ;
typedef  TYPE_2__ js_Regexp ;
struct TYPE_13__ {char* s; } ;
typedef  TYPE_3__ js_Buffer ;
struct TYPE_14__ {int nsub; TYPE_1__* sub; } ;
struct TYPE_11__ {char* sp; char const* ep; } ;
typedef  TYPE_4__ Resub ;

/* Variables and functions */
 int JS_REGEXP_G ; 
 int /*<<< orphan*/  REG_NOTBOL ; 
 char* checkstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_doregexec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ js_iscallable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushlstring (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  js_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,TYPE_3__**,char const) ; 
 int /*<<< orphan*/  js_putm (int /*<<< orphan*/ *,TYPE_3__**,char const*,char const*) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,TYPE_3__**,char const*) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 TYPE_2__* js_toregexp (int /*<<< orphan*/ *,int) ; 
 char* js_tostring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Sp_replace_regexp(js_State *J)
{
	js_Regexp *re;
	const char *source, *s, *r;
	js_Buffer *sb = NULL;
	int n, x;
	Resub m;

	source = checkstring(J, 0);
	re = js_toregexp(J, 1);

	if (js_doregexec(J, re->prog, source, &m, 0)) {
		js_copy(J, 0);
		return;
	}

	re->last = 0;

loop:
	s = m.sub[0].sp;
	n = m.sub[0].ep - m.sub[0].sp;

	if (js_iscallable(J, 2)) {
		js_copy(J, 2);
		js_pushundefined(J);
		for (x = 0; m.sub[x].sp; ++x) /* arg 0..x: substring and subexps that matched */
			js_pushlstring(J, m.sub[x].sp, m.sub[x].ep - m.sub[x].sp);
		js_pushnumber(J, s - source); /* arg x+2: offset within search string */
		js_copy(J, 0); /* arg x+3: search string */
		js_call(J, 2 + x);
		r = js_tostring(J, -1);
		js_putm(J, &sb, source, s);
		js_puts(J, &sb, r);
		js_pop(J, 1);
	} else {
		r = js_tostring(J, 2);
		js_putm(J, &sb, source, s);
		while (*r) {
			if (*r == '$') {
				switch (*(++r)) {
				case 0: --r; /* end of string; back up */
				/* fallthrough */
				case '$': js_putc(J, &sb, '$'); break;
				case '`': js_putm(J, &sb, source, s); break;
				case '\'': js_puts(J, &sb, s + n); break;
				case '&':
					js_putm(J, &sb, s, s + n);
					break;
				case '0': case '1': case '2': case '3': case '4':
				case '5': case '6': case '7': case '8': case '9':
					x = *r - '0';
					if (r[1] >= '0' && r[1] <= '9')
						x = x * 10 + *(++r) - '0';
					if (x > 0 && x < m.nsub) {
						js_putm(J, &sb, m.sub[x].sp, m.sub[x].ep);
					} else {
						js_putc(J, &sb, '$');
						if (x > 10) {
							js_putc(J, &sb, '0' + x / 10);
							js_putc(J, &sb, '0' + x % 10);
						} else {
							js_putc(J, &sb, '0' + x);
						}
					}
					break;
				default:
					js_putc(J, &sb, '$');
					js_putc(J, &sb, *r);
					break;
				}
				++r;
			} else {
				js_putc(J, &sb, *r++);
			}
		}
	}

	if (re->flags & JS_REGEXP_G) {
		source = m.sub[0].ep;
		if (n == 0) {
			if (*source)
				js_putc(J, &sb, *source++);
			else
				goto end;
		}
		if (!js_doregexec(J, re->prog, source, &m, REG_NOTBOL))
			goto loop;
	}

end:
	js_puts(J, &sb, s + n);
	js_putc(J, &sb, 0);

	if (js_try(J)) {
		js_free(J, sb);
		js_throw(J);
	}
	js_pushstring(J, sb ? sb->s : "");
	js_endtry(J);
	js_free(J, sb);
}