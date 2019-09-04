#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int dwSize; char* buffer; TYPE_1__* editstream; } ;
struct TYPE_6__ {scalar_t__ dwError; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_2__ ME_InStream ;
typedef  int LRESULT ;
typedef  int LONG ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CP_ACP ; 
 int CP_UTF8 ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  ME_InsertTextFromCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_StreamInFill (TYPE_2__*) ; 
 int MultiByteToWideChar (int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SF_UNICODE ; 
 int /*<<< orphan*/  STREAMIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,int,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcmp (char*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static LRESULT ME_StreamInText(ME_TextEditor *editor, DWORD dwFormat, ME_InStream *stream, ME_Style *style)
{
  WCHAR *pText;
  LRESULT total_bytes_read = 0;
  BOOL is_read = FALSE;
  DWORD cp = CP_ACP, copy = 0;
  char conv_buf[4 + STREAMIN_BUFFER_SIZE]; /* up to 4 additional UTF-8 bytes */

  static const char bom_utf8[] = {0xEF, 0xBB, 0xBF};

  TRACE("%08x %p\n", dwFormat, stream);

  do {
    LONG nWideChars = 0;
    WCHAR wszText[STREAMIN_BUFFER_SIZE+1];

    if (!stream->dwSize)
    {
      ME_StreamInFill(stream);
      if (stream->editstream->dwError)
        break;
      if (!stream->dwSize)
        break;
      total_bytes_read += stream->dwSize;
    }

    if (!(dwFormat & SF_UNICODE))
    {
      char * buf = stream->buffer;
      DWORD size = stream->dwSize, end;

      if (!is_read)
      {
        is_read = TRUE;
        if (stream->dwSize >= 3 && !memcmp(stream->buffer, bom_utf8, 3))
        {
          cp = CP_UTF8;
          buf += 3;
          size -= 3;
        }
      }

      if (cp == CP_UTF8)
      {
        if (copy)
        {
          memcpy(conv_buf + copy, buf, size);
          buf = conv_buf;
          size += copy;
        }
        end = size;
        while ((buf[end-1] & 0xC0) == 0x80)
        {
          --end;
          --total_bytes_read; /* strange, but seems to match windows */
        }
        if (buf[end-1] & 0x80)
        {
          DWORD need = 0;
          if ((buf[end-1] & 0xE0) == 0xC0)
            need = 1;
          if ((buf[end-1] & 0xF0) == 0xE0)
            need = 2;
          if ((buf[end-1] & 0xF8) == 0xF0)
            need = 3;

          if (size - end >= need)
          {
            /* we have enough bytes for this sequence */
            end = size;
          }
          else
          {
            /* need more bytes, so don't transcode this sequence */
            --end;
          }
        }
      }
      else
        end = size;

      nWideChars = MultiByteToWideChar(cp, 0, buf, end, wszText, STREAMIN_BUFFER_SIZE);
      pText = wszText;

      if (cp == CP_UTF8)
      {
        if (end != size)
        {
          memcpy(conv_buf, buf + end, size - end);
          copy = size - end;
        }
      }
    }
    else
    {
      nWideChars = stream->dwSize >> 1;
      pText = (WCHAR *)stream->buffer;
    }

    ME_InsertTextFromCursor(editor, 0, pText, nWideChars, style);
    if (stream->dwSize == 0)
      break;
    stream->dwSize = 0;
  } while(1);
  return total_bytes_read;
}