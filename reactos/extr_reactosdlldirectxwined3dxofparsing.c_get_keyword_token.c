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
typedef  int /*<<< orphan*/  parse_buffer ;
typedef  int /*<<< orphan*/  WORD ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_ARRAY ; 
 int /*<<< orphan*/  TOKEN_CHAR ; 
 int /*<<< orphan*/  TOKEN_CSTRING ; 
 int /*<<< orphan*/  TOKEN_DOUBLE ; 
 int /*<<< orphan*/  TOKEN_DWORD ; 
 int /*<<< orphan*/  TOKEN_FLOAT ; 
 int /*<<< orphan*/  TOKEN_LPSTR ; 
 int /*<<< orphan*/  TOKEN_SDWORD ; 
 int /*<<< orphan*/  TOKEN_SWORD ; 
 int /*<<< orphan*/  TOKEN_TEMPLATE ; 
 int /*<<< orphan*/  TOKEN_UCHAR ; 
 int /*<<< orphan*/  TOKEN_UNICODE ; 
 int /*<<< orphan*/  TOKEN_VOID ; 
 int /*<<< orphan*/  TOKEN_WORD ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static WORD get_keyword_token(parse_buffer* buf)
{
  if (is_keyword(buf, "template"))
    return TOKEN_TEMPLATE;
  if (is_keyword(buf, "WORD"))
    return TOKEN_WORD;
  if (is_keyword(buf, "DWORD"))
    return TOKEN_DWORD;
  if (is_keyword(buf, "FLOAT"))
    return TOKEN_FLOAT;
  if (is_keyword(buf, "DOUBLE"))
    return TOKEN_DOUBLE;
  if (is_keyword(buf, "CHAR"))
    return TOKEN_CHAR;
  if (is_keyword(buf, "UCHAR"))
    return TOKEN_UCHAR;
  if (is_keyword(buf, "SWORD"))
    return TOKEN_SWORD;
  if (is_keyword(buf, "SDWORD"))
    return TOKEN_SDWORD;
  if (is_keyword(buf, "VOID"))
    return TOKEN_VOID;
  if (is_keyword(buf, "STRING"))
    return TOKEN_LPSTR;
  if (is_keyword(buf, "UNICODE"))
    return TOKEN_UNICODE;
  if (is_keyword(buf, "CSTRING"))
    return TOKEN_CSTRING;
  if (is_keyword(buf, "array"))
    return TOKEN_ARRAY;

  return 0;
}