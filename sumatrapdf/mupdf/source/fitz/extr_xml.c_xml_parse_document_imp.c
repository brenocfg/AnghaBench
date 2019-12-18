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
struct parser {int dummy; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ isname (char) ; 
 scalar_t__ iswhite (char) ; 
 scalar_t__ pop_to_tag (int /*<<< orphan*/ *,struct parser*,char*,char*) ; 
 int /*<<< orphan*/  pre_open_tag (int /*<<< orphan*/ *,struct parser*,char*,char*) ; 
 char* skip_namespace_prefix (char*,char*) ; 
 int /*<<< orphan*/  xml_emit_att_name (int /*<<< orphan*/ *,struct parser*,char*,char*) ; 
 int /*<<< orphan*/  xml_emit_att_value (int /*<<< orphan*/ *,struct parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_emit_cdata (int /*<<< orphan*/ *,struct parser*,char*,char*) ; 
 int /*<<< orphan*/  xml_emit_close_tag (int /*<<< orphan*/ *,struct parser*) ; 
 int xml_emit_open_tag (int /*<<< orphan*/ *,struct parser*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_emit_text (int /*<<< orphan*/ *,struct parser*,char*,char*) ; 

__attribute__((used)) static char *xml_parse_document_imp(fz_context *ctx, struct parser *parser, char *p)
{
	char *mark;
	int quote;
	int autoclose;
	char *q;

parse_text:
	mark = p;
	while (*p && *p != '<') ++p;
	if (*p == '<') {
		/* skip trailing newline before closing tag */
		if (p[1] == '/' && mark < p - 1 && p[-1] == '\n')
			xml_emit_text(ctx, parser, mark, p - 1);
		else if (mark < p)
			xml_emit_text(ctx, parser, mark, p);
		++p;
		goto parse_element;
	} else if (mark < p)
		xml_emit_text(ctx, parser, mark, p);
	return NULL;

parse_element:
	if (*p == '/') { ++p; goto parse_closing_element; }
	if (*p == '!') { ++p; goto parse_comment; }
	if (*p == '?') { ++p; goto parse_processing_instruction; }
	while (iswhite(*p)) ++p;
	if (isname(*p))
		goto parse_element_name;
	return "syntax error in element";

parse_comment:
	if (p[0]=='D' && p[1]=='O' && p[2]=='C' && p[3]=='T' && p[4]=='Y' && p[5]=='P' && p[6]=='E')
		goto parse_declaration;
	if (p[0]=='E' && p[1]=='N' && p[2]=='T' && p[3]=='I' && p[4]=='T' && p[5]=='Y')
		goto parse_declaration;
	if (*p == '[') goto parse_cdata;
	if (*p++ != '-') return "syntax error in comment (<! not followed by --)";
	if (*p++ != '-') return "syntax error in comment (<!- not followed by -)";
	while (*p) {
		if (p[0] == '-' && p[1] == '-' && p[2] == '>') {
			p += 3;
			goto parse_text;
		}
		++p;
	}
	return "end of data in comment";

parse_declaration:
	while (*p) if (*p++ == '>') goto parse_text;
	return "end of data in declaration";

parse_cdata:
	if (p[1] != 'C' || p[2] != 'D' || p[3] != 'A' || p[4] != 'T' || p[5] != 'A' || p[6] != '[')
		return "syntax error in CDATA section";
	p += 7;
	mark = p;
	while (*p) {
		if (p[0] == ']' && p[1] == ']' && p[2] == '>') {
			xml_emit_cdata(ctx, parser, mark, p);
			p += 3;
			goto parse_text;
		}
		++p;
	}
	return "end of data in CDATA section";

parse_processing_instruction:
	while (*p) {
		if (p[0] == '?' && p[1] == '>') {
			p += 2;
			goto parse_text;
		}
		++p;
	}
	return "end of data in processing instruction";

parse_closing_element:
	while (iswhite(*p)) ++p;
	mark = p;
	while (isname(*p)) ++p;
	q = p;
	while (iswhite(*p)) ++p;
	if (*p != '>')
		return "syntax error in closing element";
	mark = skip_namespace_prefix(mark, q);
	if (pop_to_tag(ctx, parser, mark, q))
		xml_emit_close_tag(ctx, parser);
	++p;
	goto parse_text;

parse_element_name:
	mark = p;
	while (isname(*p)) ++p;
	mark = skip_namespace_prefix(mark, p);
	pre_open_tag(ctx, parser, mark, p);
	autoclose = xml_emit_open_tag(ctx, parser, mark, p, 0);
	if (*p == '>') {
		if (autoclose)
			xml_emit_close_tag(ctx, parser);
		++p;
		if (*p == '\n') ++p; /* must skip linebreak immediately after an opening tag */
		goto parse_text;
	}
	if (p[0] == '/' && p[1] == '>') {
		xml_emit_close_tag(ctx, parser);
		p += 2;
		goto parse_text;
	}
	if (iswhite(*p))
		goto parse_attributes;
	return "syntax error after element name";

parse_attributes:
	while (iswhite(*p)) ++p;
	if (isname(*p))
		goto parse_attribute_name;
	if (*p == '>') {
		if (autoclose)
			xml_emit_close_tag(ctx, parser);
		++p;
		if (*p == '\n') ++p; /* must skip linebreak immediately after an opening tag */
		goto parse_text;
	}
	if (p[0] == '/' && p[1] == '>') {
		xml_emit_close_tag(ctx, parser);
		p += 2;
		goto parse_text;
	}
	return "syntax error in attributes";

parse_attribute_name:
	mark = p;
	while (isname(*p)) ++p;
	xml_emit_att_name(ctx, parser, mark, p);
	while (iswhite(*p)) ++p;
	if (*p == '=') { ++p; goto parse_attribute_value; }
	return "syntax error after attribute name";

parse_attribute_value:
	while (iswhite(*p)) ++p;
	quote = *p++;
	if (quote != '"' && quote != '\'')
		return "missing quote character";
	mark = p;
	while (*p && *p != quote) ++p;
	if (*p == quote) {
		xml_emit_att_value(ctx, parser, mark, p++);
		goto parse_attributes;
	}
	return "end of data in attribute value";
}