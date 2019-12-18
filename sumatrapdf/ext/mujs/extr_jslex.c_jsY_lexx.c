#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  text; } ;
struct TYPE_18__ {int newline; char lexchar; TYPE_1__ lexbuf; int /*<<< orphan*/  lasttoken; int /*<<< orphan*/  line; int /*<<< orphan*/  lexline; } ;
typedef  TYPE_2__ js_State ;

/* Variables and functions */
 int TK_ADD_ASS ; 
 int TK_AND ; 
 int TK_AND_ASS ; 
 int TK_DEC ; 
 int TK_DIV_ASS ; 
 int TK_EQ ; 
 int TK_GE ; 
 int TK_INC ; 
 int TK_LE ; 
 int TK_MOD_ASS ; 
 int TK_MUL_ASS ; 
 int TK_NE ; 
 int TK_OR ; 
 int TK_OR_ASS ; 
 int TK_SHL ; 
 int TK_SHL_ASS ; 
 int TK_SHR ; 
 int TK_SHR_ASS ; 
 int TK_STRICTEQ ; 
 int TK_STRICTNE ; 
 int TK_SUB_ASS ; 
 int TK_USHR ; 
 int TK_USHR_ASS ; 
 int TK_XOR_ASS ; 
 scalar_t__ isnlthcontext (int /*<<< orphan*/ ) ; 
 scalar_t__ isregexpcontext (int /*<<< orphan*/ ) ; 
 scalar_t__ jsY_accept (TYPE_2__*,char) ; 
 int /*<<< orphan*/  jsY_error (TYPE_2__*,char*,...) ; 
 int jsY_findkeyword (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ jsY_isidentifierpart (char) ; 
 scalar_t__ jsY_isidentifierstart (char) ; 
 scalar_t__ jsY_iswhite (char) ; 
 int /*<<< orphan*/  jsY_next (TYPE_2__*) ; 
 int /*<<< orphan*/  jsY_unescape (TYPE_2__*) ; 
 scalar_t__ lexcomment (TYPE_2__*) ; 
 int /*<<< orphan*/  lexlinecomment (TYPE_2__*) ; 
 int lexnumber (TYPE_2__*) ; 
 int lexregexp (TYPE_2__*) ; 
 int lexstring (TYPE_2__*) ; 
 int /*<<< orphan*/  textend (TYPE_2__*) ; 
 int /*<<< orphan*/  textinit (TYPE_2__*) ; 
 int /*<<< orphan*/  textpush (TYPE_2__*,char) ; 

__attribute__((used)) static int jsY_lexx(js_State *J)
{
	J->newline = 0;

	while (1) {
		J->lexline = J->line; /* save location of beginning of token */

		while (jsY_iswhite(J->lexchar))
			jsY_next(J);

		if (jsY_accept(J, '\n')) {
			J->newline = 1;
			if (isnlthcontext(J->lasttoken))
				return ';';
			continue;
		}

		if (jsY_accept(J, '/')) {
			if (jsY_accept(J, '/')) {
				lexlinecomment(J);
				continue;
			} else if (jsY_accept(J, '*')) {
				if (lexcomment(J))
					jsY_error(J, "multi-line comment not terminated");
				continue;
			} else if (isregexpcontext(J->lasttoken)) {
				return lexregexp(J);
			} else if (jsY_accept(J, '=')) {
				return TK_DIV_ASS;
			} else {
				return '/';
			}
		}

		if (J->lexchar >= '0' && J->lexchar <= '9') {
			return lexnumber(J);
		}

		switch (J->lexchar) {
		case '(': jsY_next(J); return '(';
		case ')': jsY_next(J); return ')';
		case ',': jsY_next(J); return ',';
		case ':': jsY_next(J); return ':';
		case ';': jsY_next(J); return ';';
		case '?': jsY_next(J); return '?';
		case '[': jsY_next(J); return '[';
		case ']': jsY_next(J); return ']';
		case '{': jsY_next(J); return '{';
		case '}': jsY_next(J); return '}';
		case '~': jsY_next(J); return '~';

		case '\'':
		case '"':
			return lexstring(J);

		case '.':
			return lexnumber(J);

		case '<':
			jsY_next(J);
			if (jsY_accept(J, '<')) {
				if (jsY_accept(J, '='))
					return TK_SHL_ASS;
				return TK_SHL;
			}
			if (jsY_accept(J, '='))
				return TK_LE;
			return '<';

		case '>':
			jsY_next(J);
			if (jsY_accept(J, '>')) {
				if (jsY_accept(J, '>')) {
					if (jsY_accept(J, '='))
						return TK_USHR_ASS;
					return TK_USHR;
				}
				if (jsY_accept(J, '='))
					return TK_SHR_ASS;
				return TK_SHR;
			}
			if (jsY_accept(J, '='))
				return TK_GE;
			return '>';

		case '=':
			jsY_next(J);
			if (jsY_accept(J, '=')) {
				if (jsY_accept(J, '='))
					return TK_STRICTEQ;
				return TK_EQ;
			}
			return '=';

		case '!':
			jsY_next(J);
			if (jsY_accept(J, '=')) {
				if (jsY_accept(J, '='))
					return TK_STRICTNE;
				return TK_NE;
			}
			return '!';

		case '+':
			jsY_next(J);
			if (jsY_accept(J, '+'))
				return TK_INC;
			if (jsY_accept(J, '='))
				return TK_ADD_ASS;
			return '+';

		case '-':
			jsY_next(J);
			if (jsY_accept(J, '-'))
				return TK_DEC;
			if (jsY_accept(J, '='))
				return TK_SUB_ASS;
			return '-';

		case '*':
			jsY_next(J);
			if (jsY_accept(J, '='))
				return TK_MUL_ASS;
			return '*';

		case '%':
			jsY_next(J);
			if (jsY_accept(J, '='))
				return TK_MOD_ASS;
			return '%';

		case '&':
			jsY_next(J);
			if (jsY_accept(J, '&'))
				return TK_AND;
			if (jsY_accept(J, '='))
				return TK_AND_ASS;
			return '&';

		case '|':
			jsY_next(J);
			if (jsY_accept(J, '|'))
				return TK_OR;
			if (jsY_accept(J, '='))
				return TK_OR_ASS;
			return '|';

		case '^':
			jsY_next(J);
			if (jsY_accept(J, '='))
				return TK_XOR_ASS;
			return '^';

		case 0:
			return 0; /* EOF */
		}

		/* Handle \uXXXX escapes in identifiers */
		jsY_unescape(J);
		if (jsY_isidentifierstart(J->lexchar)) {
			textinit(J);
			textpush(J, J->lexchar);

			jsY_next(J);
			jsY_unescape(J);
			while (jsY_isidentifierpart(J->lexchar)) {
				textpush(J, J->lexchar);
				jsY_next(J);
				jsY_unescape(J);
			}

			textend(J);

			return jsY_findkeyword(J, J->lexbuf.text);
		}

		if (J->lexchar >= 0x20 && J->lexchar <= 0x7E)
			jsY_error(J, "unexpected character: '%c'", J->lexchar);
		jsY_error(J, "unexpected character: \\u%04X", J->lexchar);
	}
}