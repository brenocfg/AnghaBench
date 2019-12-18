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
struct parser {char* start; } ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  COMMENT ; 
 int /*<<< orphan*/  EOL_BACKSLASH ; 
 int /*<<< orphan*/  KEY_NAME ; 
 int /*<<< orphan*/  LEADING_SPACES ; 
 int /*<<< orphan*/  LINE_START ; 
 int /*<<< orphan*/  QUOTES ; 
 int /*<<< orphan*/  TRAILING_SPACES ; 
 int /*<<< orphan*/  VALUE_NAME ; 
 int /*<<< orphan*/  add_field_from_token (struct parser*,int) ; 
 int /*<<< orphan*/  is_eol (struct parser*,char const*) ; 
 int /*<<< orphan*/  isspaceW (char const) ; 
 int /*<<< orphan*/  push_state (struct parser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_token (struct parser*,char const*) ; 
 int /*<<< orphan*/  set_state (struct parser*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const WCHAR *key_name_state( struct parser *parser, const WCHAR *pos )
{
    const WCHAR *p, *token_end = parser->start;

    for (p = pos; !is_eol( parser, p ); p++)
    {
        if (*p == ',') break;
        switch(*p)
        {

         case '=':
            push_token( parser, token_end );
            if (!add_field_from_token( parser, 1 )) return NULL;
            parser->start = p + 1;
            push_state( parser, VALUE_NAME );
            set_state( parser, LEADING_SPACES );
            return p + 1;
        case ';':
            push_token( parser, token_end );
            if (!add_field_from_token( parser, 0 )) return NULL;
            push_state( parser, LINE_START );
            set_state( parser, COMMENT );
            return p + 1;
        case '"':
            push_token( parser, token_end );
            parser->start = p + 1;
            push_state( parser, KEY_NAME );
            set_state( parser, QUOTES );
            return p + 1;
        case '\\':
            push_token( parser, token_end );
            parser->start = p;
            push_state( parser, KEY_NAME );
            set_state( parser, EOL_BACKSLASH );
            return p;
        default:
            if (!isspaceW(*p)) token_end = p + 1;
            else
            {
                push_token( parser, p );
                push_state( parser, KEY_NAME );
                set_state( parser, TRAILING_SPACES );
                return p;
            }
            break;
        }
    }
    push_token( parser, token_end );
    set_state( parser, VALUE_NAME );
    return p;
}