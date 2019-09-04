#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_5__ {scalar_t__ nDefaultCodePage; scalar_t__ nCodePage; } ;
typedef  TYPE_1__ ME_OutStream ;
typedef  int LONG ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CP_SYMBOL ; 
 scalar_t__ CP_UTF8 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ME_StreamOutMove (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  ME_StreamOutPrint (TYPE_1__*,char*,int,char*) ; 
 int STREAMOUT_BUFFER_SIZE ; 
 int WideCharToMultiByte (scalar_t__,int /*<<< orphan*/ ,int const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenW (int const*) ; 
 int min (int,int) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static BOOL
ME_StreamOutRTFText(ME_OutStream *pStream, const WCHAR *text, LONG nChars)
{
  char buffer[STREAMOUT_BUFFER_SIZE];
  int pos = 0;
  int fit, nBytes, i;

  if (nChars == -1)
    nChars = lstrlenW(text);
  
  while (nChars) {
    /* In UTF-8 mode, font charsets are not used. */
    if (pStream->nDefaultCodePage == CP_UTF8) {
      /* 6 is the maximum character length in UTF-8 */
      fit = min(nChars, STREAMOUT_BUFFER_SIZE / 6);
      nBytes = WideCharToMultiByte(CP_UTF8, 0, text, fit, buffer,
                                   STREAMOUT_BUFFER_SIZE, NULL, NULL);
      nChars -= fit;
      text += fit;
      for (i = 0; i < nBytes; i++)
        if (buffer[i] == '{' || buffer[i] == '}' || buffer[i] == '\\') {
          if (!ME_StreamOutPrint(pStream, "%.*s\\", i - pos, buffer + pos))
            return FALSE;
          pos = i;
        }
      if (pos < nBytes)
        if (!ME_StreamOutMove(pStream, buffer + pos, nBytes - pos))
          return FALSE;
      pos = 0;
    } else if (*text < 128) {
      if (*text == '{' || *text == '}' || *text == '\\')
        buffer[pos++] = '\\';
      buffer[pos++] = (char)(*text++);
      nChars--;
    } else {
      BOOL unknown = FALSE;
      char letter[3];

      /* FIXME: In the MS docs for WideCharToMultiByte there is a big list of
       * codepages including CP_SYMBOL for which the last parameter must be set
       * to NULL for the function to succeed. But in Wine we need to care only
       * about CP_SYMBOL */
      nBytes = WideCharToMultiByte(pStream->nCodePage, 0, text, 1,
                                   letter, 3, NULL,
                                   (pStream->nCodePage == CP_SYMBOL) ? NULL : &unknown);
      if (unknown)
        pos += sprintf(buffer + pos, "\\u%d?", (short)*text);
      else if ((BYTE)*letter < 128) {
        if (*letter == '{' || *letter == '}' || *letter == '\\')
          buffer[pos++] = '\\';
        buffer[pos++] = *letter;
      } else {
         for (i = 0; i < nBytes; i++)
           pos += sprintf(buffer + pos, "\\'%02x", (BYTE)letter[i]);
      }
      text++;
      nChars--;
    }
    if (pos >= STREAMOUT_BUFFER_SIZE - 11) {
      if (!ME_StreamOutMove(pStream, buffer, pos))
        return FALSE;
      pos = 0;
    }
  }
  return ME_StreamOutMove(pStream, buffer, pos);
}