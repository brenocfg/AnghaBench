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
typedef  int /*<<< orphan*/  lpBuf ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int* PDWORD ;
typedef  int* LPTSTR ;
typedef  int INT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int CHAR_NEWLINE ; 
 int CHAR_NULL ; 
 int /*<<< orphan*/  COUNTOF (int /*<<< orphan*/ *) ; 
 int DE_BEGIN ; 
 int ERROR_EXTENDED_ERROR ; 
 scalar_t__ ERROR_RESOURCE_LANG_NOT_FOUND ; 
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int FORMAT_MESSAGE_MAX_WIDTH_MASK ; 
 int FormatMessage (int,int /*<<< orphan*/ *,int,scalar_t__,int*,int,int /*<<< orphan*/ *) ; 
 int* FormatSuggest (int) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int LoadString (int /*<<< orphan*/ ,int,int*,int) ; 
 scalar_t__ MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int SUG_IGN_FORMATMESSAGE ; 
 scalar_t__ WAITNET_LOADED ; 
 int /*<<< orphan*/  WNetGetLastError (int*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hAppInstance ; 
 int /*<<< orphan*/  lcid ; 
 int lstrlen (int*) ; 

DWORD
FormatError(
   BOOL bNullString,
   LPTSTR lpBuf,
   INT iSize,
   DWORD dwError)
{
   INT iLen;
   DWORD dwNumChars = 0;
   PDWORD pdwSuggest;
   INT iAddNewline = 0;

   WORD wLangId;
   BOOL bTryAgain;

   //
   // If error == 0, just return...
   //
   if (!dwError)
      return 0;

   if (bNullString)
      lpBuf[0] = 0;

   iLen = lstrlen(lpBuf);

   lpBuf += iLen;
   iSize -= iLen;

   if (iSize <=0)
      return 0;

   // Check suggestion flags before calling FormatMessage
   // in case we want to use our own string.

   pdwSuggest = FormatSuggest( dwError );

   //
   // Only do a FormatMessage if the DE_BIT is off and the
   // SUG_IGN_FORMATMESSAGE bit is off.
   // (If no suggestion, default use format message)
   //

   if ( !(dwError & DE_BEGIN) &&
      !(pdwSuggest && pdwSuggest[1] & SUG_IGN_FORMATMESSAGE) ) {

      // if extended error, use WNetErrorText!
      if ( ERROR_EXTENDED_ERROR == dwError ) {
         DWORD dwErrorCode;
         TCHAR szProvider[128];


         if (WAITNET_LOADED) {

            // !! BUG: szProvider size hard coded, doesn't print provider !!

            WNetGetLastError( &dwErrorCode, lpBuf, iSize, szProvider,
               COUNTOF(szProvider));
         }

         return lstrlen(lpBuf);
      }

      //
      // Begin with language from thread.
      //
      // loop again only if the there is an error,
      //    the error is that the resource lang isn't found,
      //    and we are not using the neutral language.
      //
      // If so, repeat query using neutral language.
      //
      wLangId = LANGIDFROMLCID(lcid);

      do {
         dwNumChars = FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM |
               FORMAT_MESSAGE_IGNORE_INSERTS |
               FORMAT_MESSAGE_MAX_WIDTH_MASK,
            NULL, dwError, wLangId,
            lpBuf, iSize*sizeof(lpBuf[0]), NULL );

         bTryAgain = !dwNumChars &&
            MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL) != wLangId &&
            ERROR_RESOURCE_LANG_NOT_FOUND == GetLastError();

         wLangId = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

      } while (bTryAgain);

      iAddNewline = 2;
   }

   //
   // if !dwNumChars, NULL terminate for safety.
   //
   if (!dwNumChars) {
      lpBuf[0] = CHAR_NULL;
   }

   //
   // Now add suggestion if it exists.
   //
   if (pdwSuggest && pdwSuggest[2]) {

      DWORD dwNumTemp = 0;

      // Make sure we have space:

      lpBuf += dwNumChars + iAddNewline;
      iSize -= dwNumChars + iAddNewline;

      if (!iSize)
         goto SuggestPunt;

      //
      // We found one, add a new line in for formatting
      //

      for(;iAddNewline; iAddNewline--)
         lpBuf[-iAddNewline] = CHAR_NEWLINE;

      dwNumTemp = LoadString ( hAppInstance, pdwSuggest[2], lpBuf, iSize );

      return dwNumTemp+dwNumChars+iAddNewline;
   }

SuggestPunt:

   // if dwNumChars != 0 then just make sure last char
   // isn't \n.  if it is, strip it!

   if ( dwNumChars ) {
      if ( CHAR_NEWLINE == lpBuf[dwNumChars-1] ) {
         lpBuf[dwNumChars-1] = CHAR_NULL;
      }

      if ( dwNumChars > 1 ) {
         if ( 0x000D == lpBuf[dwNumChars-2] ) {
            lpBuf[dwNumChars-2] = CHAR_NULL;
         }
      }
   }

   return dwNumChars;
}