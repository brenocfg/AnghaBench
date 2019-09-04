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
typedef  int* LPWSTR ;
typedef  int BOOL ;

/* Variables and functions */
 int CHAR_DOT ; 
 int CHAR_NULL ; 
#define  CHAR_QUESTION 129 
#define  CHAR_STAR 128 
 int* CharNext (int*) ; 
 int FALSE ; 
 int /*<<< orphan*/  SZ_STAR ; 
 int TRUE ; 
 int /*<<< orphan*/  lstrcmp (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szStarDotStar ; 

BOOL
MatchFile(LPWSTR szFile, LPWSTR szSpec)
{

#define IS_DOTEND(ch)   ((ch) == CHAR_DOT || (ch) == CHAR_NULL)

   if (!lstrcmp(szSpec, SZ_STAR) ||            // "*" matches everything
      !lstrcmp(szSpec, szStarDotStar))         // so does "*.*"
      return TRUE;

   while (*szFile && *szSpec) {

      switch (*szSpec) {
      case CHAR_QUESTION:
         szFile++;
         szSpec++;
         break;

      case CHAR_STAR:

         while (!IS_DOTEND(*szSpec))     // got till a terminator
            szSpec = CharNext(szSpec);

         if (*szSpec == CHAR_DOT)
            szSpec++;

         while (!IS_DOTEND(*szFile))     // got till a terminator
            szFile = CharNext(szFile);

         if (*szFile == CHAR_DOT)
            szFile++;

         break;

      default:
         if (*szSpec == *szFile) {

            szFile++;
            szSpec++;
         } else
            return FALSE;
      }
   }
   return !*szFile && !*szSpec;
}