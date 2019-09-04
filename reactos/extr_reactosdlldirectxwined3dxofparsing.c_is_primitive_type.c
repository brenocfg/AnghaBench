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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  TOKEN_CHAR 138 
#define  TOKEN_CSTRING 137 
#define  TOKEN_DOUBLE 136 
#define  TOKEN_DWORD 135 
#define  TOKEN_FLOAT 134 
#define  TOKEN_LPSTR 133 
#define  TOKEN_SDWORD 132 
#define  TOKEN_SWORD 131 
#define  TOKEN_UCHAR 130 
#define  TOKEN_UNICODE 129 
#define  TOKEN_WORD 128 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline BOOL is_primitive_type(WORD token)
{
  BOOL ret;
  switch(token)
  {
    case TOKEN_WORD:
    case TOKEN_DWORD:
    case TOKEN_FLOAT:
    case TOKEN_DOUBLE:
    case TOKEN_CHAR:
    case TOKEN_UCHAR:
    case TOKEN_SWORD:
    case TOKEN_SDWORD:
    case TOKEN_LPSTR:
    case TOKEN_UNICODE:
    case TOKEN_CSTRING:
      ret = TRUE;
      break;
    default:
      ret = FALSE;
      break;
  }
  return ret;
}