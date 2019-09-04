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
typedef  int WORD ;

/* Variables and functions */
#define  TOKEN_ARRAY 158 
#define  TOKEN_CANGLE 157 
#define  TOKEN_CBRACE 156 
#define  TOKEN_CBRACKET 155 
#define  TOKEN_CHAR 154 
#define  TOKEN_COMMA 153 
#define  TOKEN_CPAREN 152 
#define  TOKEN_CSTRING 151 
#define  TOKEN_DOT 150 
#define  TOKEN_DOUBLE 149 
#define  TOKEN_DWORD 148 
#define  TOKEN_FLOAT 147 
#define  TOKEN_FLOAT_LIST 146 
#define  TOKEN_GUID 145 
#define  TOKEN_INTEGER 144 
#define  TOKEN_INTEGER_LIST 143 
#define  TOKEN_LPSTR 142 
#define  TOKEN_NAME 141 
#define  TOKEN_OANGLE 140 
#define  TOKEN_OBRACE 139 
#define  TOKEN_OBRACKET 138 
#define  TOKEN_OPAREN 137 
#define  TOKEN_SDWORD 136 
#define  TOKEN_SEMICOLON 135 
#define  TOKEN_STRING 134 
#define  TOKEN_SWORD 133 
#define  TOKEN_TEMPLATE 132 
#define  TOKEN_UCHAR 131 
#define  TOKEN_UNICODE 130 
#define  TOKEN_VOID 129 
#define  TOKEN_WORD 128 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static void dump_TOKEN(WORD token)
{
#define DUMP_TOKEN(t) case t: TRACE(#t "\n"); break
  switch(token)
  {
    DUMP_TOKEN(TOKEN_NAME);
    DUMP_TOKEN(TOKEN_STRING);
    DUMP_TOKEN(TOKEN_INTEGER);
    DUMP_TOKEN(TOKEN_GUID);
    DUMP_TOKEN(TOKEN_INTEGER_LIST);
    DUMP_TOKEN(TOKEN_FLOAT_LIST);
    DUMP_TOKEN(TOKEN_OBRACE);
    DUMP_TOKEN(TOKEN_CBRACE);
    DUMP_TOKEN(TOKEN_OPAREN);
    DUMP_TOKEN(TOKEN_CPAREN);
    DUMP_TOKEN(TOKEN_OBRACKET);
    DUMP_TOKEN(TOKEN_CBRACKET);
    DUMP_TOKEN(TOKEN_OANGLE);
    DUMP_TOKEN(TOKEN_CANGLE);
    DUMP_TOKEN(TOKEN_DOT);
    DUMP_TOKEN(TOKEN_COMMA);
    DUMP_TOKEN(TOKEN_SEMICOLON);
    DUMP_TOKEN(TOKEN_TEMPLATE);
    DUMP_TOKEN(TOKEN_WORD);
    DUMP_TOKEN(TOKEN_DWORD);
    DUMP_TOKEN(TOKEN_FLOAT);
    DUMP_TOKEN(TOKEN_DOUBLE);
    DUMP_TOKEN(TOKEN_CHAR);
    DUMP_TOKEN(TOKEN_UCHAR);
    DUMP_TOKEN(TOKEN_SWORD);
    DUMP_TOKEN(TOKEN_SDWORD);
    DUMP_TOKEN(TOKEN_VOID);
    DUMP_TOKEN(TOKEN_LPSTR);
    DUMP_TOKEN(TOKEN_UNICODE);
    DUMP_TOKEN(TOKEN_CSTRING);
    DUMP_TOKEN(TOKEN_ARRAY);
    default:
      if (0)
        TRACE("Unknown token %d\n", token);
      break;
  }
#undef DUMP_TOKEN
}