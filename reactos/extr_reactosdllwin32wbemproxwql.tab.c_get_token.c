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
typedef  int WCHAR ;

/* Variables and functions */
 int TK_COMMA ; 
 int TK_DOT ; 
 int TK_EQ ; 
 int TK_GE ; 
 int TK_GT ; 
 int TK_ILLEGAL ; 
 int TK_INTEGER ; 
 int TK_LE ; 
 int TK_LP ; 
 int TK_LT ; 
 int TK_MINUS ; 
 int TK_NE ; 
 int TK_RP ; 
 int TK_SPACE ; 
 int TK_STAR ; 
 int TK_STRING ; 
 int /*<<< orphan*/ * id_char ; 
 int /*<<< orphan*/  isdigitW (int const) ; 
 int /*<<< orphan*/  isspaceW (int const) ; 
 int keyword_type (int const*,int) ; 

__attribute__((used)) static int get_token( const WCHAR *s, int *token )
{
    int i;

    switch (*s)
    {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        for (i = 1; isspaceW( s[i] ); i++) {}
        *token = TK_SPACE;
        return i;
    case '-':
        if (!s[1]) return -1;
        *token = TK_MINUS;
        return 1;
    case '(':
        *token = TK_LP;
        return 1;
    case ')':
        *token = TK_RP;
        return 1;
    case '*':
        *token = TK_STAR;
        return 1;
    case '=':
        *token = TK_EQ;
        return 1;
    case '<':
        if (s[1] == '=' )
        {
            *token = TK_LE;
            return 2;
        }
        else if (s[1] == '>')
        {
            *token = TK_NE;
            return 2;
        }
        else
        {
            *token = TK_LT;
            return 1;
        }
    case '>':
        if (s[1] == '=')
        {
            *token = TK_GE;
            return 2;
        }
        else
        {
            *token = TK_GT;
            return 1;
        }
    case '!':
        if (s[1] != '=')
        {
            *token = TK_ILLEGAL;
            return 2;
        }
        else
        {
            *token = TK_NE;
            return 2;
        }
    case ',':
        *token = TK_COMMA;
        return 1;
    case '\"':
    case '\'':
        for (i = 1; s[i]; i++)
        {
            if (s[i] == s[0]) break;
        }
        if (s[i]) i++;
        *token = TK_STRING;
        return i;
    case '.':
        if (!isdigitW( s[1] ))
        {
            *token = TK_DOT;
            return 1;
        }
        /* fall through */
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        *token = TK_INTEGER;
        for (i = 1; isdigitW( s[i] ); i++) {}
        return i;
    default:
        if (!id_char[*s]) break;

        for (i = 1; id_char[s[i]]; i++) {}
        *token = keyword_type( s, i );
        return i;
    }
    *token = TK_ILLEGAL;
    return 1;
}