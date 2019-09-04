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
typedef  int TUCHAR ;
typedef  int BOOL ;

/* Variables and functions */
#define  CHAR_BACKSLASH 139 
#define  CHAR_COLON 138 
#define  CHAR_COMMA 137 
#define  CHAR_DQUOTE 136 
#define  CHAR_GREATER 135 
#define  CHAR_LESS 134 
#define  CHAR_PIPE 133 
#define  CHAR_QUESTION 132 
#define  CHAR_SEMICOLON 131 
#define  CHAR_SLASH 130 
#define  CHAR_SPACE 129 
#define  CHAR_STAR 128 
 int FALSE ; 

BOOL
IsValidChar(TUCHAR ch, BOOL fPath, BOOL bLFN)
{
   switch (ch) {
   case CHAR_SEMICOLON:   // terminator
   case CHAR_COMMA:       // terminator
      return bLFN;

   case CHAR_PIPE:       // pipe
   case CHAR_GREATER:    // redir
   case CHAR_LESS:       // redir
   case CHAR_DQUOTE:     // quote
      return FALSE;

   case CHAR_QUESTION:    // wc           we only do wilds here because they're
   case CHAR_STAR:        // wc           legal for qualifypath
   case CHAR_BACKSLASH:   // path separator
   case CHAR_COLON:       // drive colon
   case CHAR_SLASH:       // path sep
   case CHAR_SPACE:       // space: valid on NT FAT, but winball can't use.
      return fPath;
   }

   //
   // cannot be a control character or space
   //
   return ch > CHAR_SPACE;
}