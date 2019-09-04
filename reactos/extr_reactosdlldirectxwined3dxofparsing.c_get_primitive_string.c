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
typedef  int DWORD ;

/* Variables and functions */
#define  TOKEN_CHAR 139 
#define  TOKEN_CSTRING 138 
#define  TOKEN_DOUBLE 137 
#define  TOKEN_DWORD 136 
#define  TOKEN_FLOAT 135 
#define  TOKEN_LPSTR 134 
#define  TOKEN_SDWORD 133 
#define  TOKEN_SWORD 132 
#define  TOKEN_UCHAR 131 
#define  TOKEN_UNICODE 130 
#define  TOKEN_VOID 129 
#define  TOKEN_WORD 128 

__attribute__((used)) static const char* get_primitive_string(DWORD token)
{
  switch(token)
  {
    case TOKEN_WORD:
      return "WORD";
    case TOKEN_DWORD:
      return "DWORD";
    case TOKEN_FLOAT:
      return "FLOAT";
    case TOKEN_DOUBLE:
      return "DOUBLE";
    case TOKEN_CHAR:
      return "CHAR";
    case TOKEN_UCHAR:
      return "UCHAR";
    case TOKEN_SWORD:
      return "SWORD";
    case TOKEN_SDWORD:
      return "SDWORD";
    case TOKEN_VOID:
      return "VOID";
    case TOKEN_LPSTR:
      return "STRING";
    case TOKEN_UNICODE:
      return "UNICODE";
    case TOKEN_CSTRING:
      return "CSTRING ";
    default:
      break;
  }
  return NULL;
}