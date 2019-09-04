#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_83__   TYPE_9__ ;
typedef  struct TYPE_82__   TYPE_8__ ;
typedef  struct TYPE_81__   TYPE_7__ ;
typedef  struct TYPE_80__   TYPE_6__ ;
typedef  struct TYPE_79__   TYPE_5__ ;
typedef  struct TYPE_78__   TYPE_4__ ;
typedef  struct TYPE_77__   TYPE_45__ ;
typedef  struct TYPE_76__   TYPE_3__ ;
typedef  struct TYPE_75__   TYPE_2__ ;
typedef  struct TYPE_74__   TYPE_1__ ;
typedef  struct TYPE_73__   TYPE_14__ ;
typedef  struct TYPE_72__   TYPE_13__ ;
typedef  struct TYPE_71__   TYPE_12__ ;
typedef  struct TYPE_70__   TYPE_11__ ;
typedef  struct TYPE_69__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cf ;
typedef  char WCHAR ;
struct TYPE_83__ {int nEventMask; int mode; int nUndoMode; int /*<<< orphan*/  texthost; TYPE_12__* pCursors; scalar_t__ bEmulateVersion10; TYPE_3__* pBuffer; } ;
struct TYPE_82__ {int rtfFormat; int nestingLevel; scalar_t__ stackTop; int /*<<< orphan*/ * style; TYPE_7__* stack; TYPE_6__* tableDef; int /*<<< orphan*/  rtfMinor; scalar_t__ canInheritInTbl; TYPE_9__* editor; } ;
struct TYPE_81__ {int /*<<< orphan*/ * style; } ;
struct TYPE_80__ {TYPE_11__* tableRowStart; } ;
struct TYPE_78__ {int nFlags; TYPE_11__* next_para; int /*<<< orphan*/  fmt; } ;
struct TYPE_79__ {TYPE_4__ para; } ;
struct TYPE_74__ {int nFlags; } ;
struct TYPE_75__ {TYPE_1__ run; } ;
struct TYPE_77__ {TYPE_2__ member; } ;
struct TYPE_76__ {int /*<<< orphan*/ * pDefaultStyle; } ;
struct TYPE_73__ {int cbSize; int /*<<< orphan*/  dwMask; } ;
struct TYPE_72__ {int dwError; } ;
struct TYPE_71__ {scalar_t__ nOffset; TYPE_45__* pRun; TYPE_11__* pPara; } ;
struct TYPE_70__ {TYPE_5__ member; } ;
struct TYPE_69__ {char* buffer; TYPE_13__* editstream; scalar_t__ dwUsed; scalar_t__ dwSize; } ;
typedef  TYPE_8__ RTF_Info ;
typedef  TYPE_9__ ME_TextEditor ;
typedef  int /*<<< orphan*/  ME_Style ;
typedef  TYPE_10__ ME_InStream ;
typedef  TYPE_11__ ME_DisplayItem ;
typedef  TYPE_12__ ME_Cursor ;
typedef  int LRESULT ;
typedef  TYPE_13__ EDITSTREAM ;
typedef  int DWORD ;
typedef  TYPE_14__ CHARFORMAT2W ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BeginFile (TYPE_8__*) ; 
 int /*<<< orphan*/  CFM_ALL2 ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  ERROR_HANDLE_EOF ; 
 scalar_t__ FALSE ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITextHost_TxShowCaret (int /*<<< orphan*/ ,scalar_t__) ; 
 int MEPF_ROWEND ; 
 int MEPF_ROWSTART ; 
 int MERF_ENDPARA ; 
 int /*<<< orphan*/  ME_AddRefStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_CheckTablesForCorruption (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_ClearTempStyle (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_CommitUndo (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_CursorFromCharOfs (TYPE_9__*,int,TYPE_12__*) ; 
 int /*<<< orphan*/  ME_EmptyUndoStack (TYPE_9__*) ; 
 void* ME_FindItemFwd (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ME_GetCharFormat (TYPE_9__*,TYPE_12__*,TYPE_12__*,TYPE_14__*) ; 
 int ME_GetCursorOfs (TYPE_12__*) ; 
 int /*<<< orphan*/  ME_GetSelection (TYPE_9__*,TYPE_12__**,TYPE_12__**) ; 
 int /*<<< orphan*/ * ME_GetSelectionInsertStyle (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_GetSelectionOfs (TYPE_9__*,int*,int*) ; 
 int ME_GetTextLength (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_GetTextW (TYPE_9__*,char*,int,TYPE_12__*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ME_InternalDeleteText (TYPE_9__*,TYPE_12__*,int,scalar_t__) ; 
 scalar_t__ ME_IsInTable (TYPE_45__*) ; 
 int /*<<< orphan*/  ME_MoveCaret (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_MoveCursorChars (TYPE_9__*,TYPE_12__*,int,scalar_t__) ; 
 int /*<<< orphan*/  ME_RTFReadHook ; 
 int /*<<< orphan*/  ME_RTFReadObjectGroup ; 
 int /*<<< orphan*/  ME_RTFReadParnumGroup ; 
 int /*<<< orphan*/  ME_RTFReadPictGroup ; 
 int /*<<< orphan*/  ME_RTFReadShpPictGroup ; 
 int /*<<< orphan*/  ME_RTFSpecialCharHook (TYPE_8__*) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SendRequestResize (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  ME_SendSelChange (TYPE_9__*) ; 
 int /*<<< orphan*/  ME_SetDefaultParaFormat (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_SetSelection (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  ME_SetSelectionCharFormat (TYPE_9__*,TYPE_14__*) ; 
 int /*<<< orphan*/  ME_StreamInFill (TYPE_10__*) ; 
 int ME_StreamInText (TYPE_9__*,int,TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ME_UpdateLinkAttribute (TYPE_9__*,TYPE_12__*,int) ; 
 int /*<<< orphan*/  ME_UpdateRepaint (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  RTFDestroy (TYPE_8__*) ; 
 int /*<<< orphan*/  RTFFlushOutputBuffer (TYPE_8__*) ; 
 int /*<<< orphan*/  RTFInit (TYPE_8__*) ; 
 int /*<<< orphan*/  RTFRead (TYPE_8__*) ; 
 int /*<<< orphan*/  RTFReadGroup ; 
 int /*<<< orphan*/  RTFSetDestinationCallback (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFSetEditStream (TYPE_8__*,TYPE_10__*) ; 
 int /*<<< orphan*/  RTFSetReadHook (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTFSkipGroup ; 
 int SFF_SELECTION ; 
 int SF_RTF ; 
 int SF_TEXT ; 
 int TM_RICHTEXT ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_13__*,TYPE_9__*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WriterInit (TYPE_8__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  diRun ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtfNestTableProps ; 
 int /*<<< orphan*/  rtfNoNestTables ; 
 int /*<<< orphan*/  rtfObject ; 
 int /*<<< orphan*/  rtfParNumbering ; 
 int /*<<< orphan*/  rtfPict ; 
 int /*<<< orphan*/  rtfRow ; 
 int /*<<< orphan*/  rtfShpPict ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int umIgnore ; 

__attribute__((used)) static LRESULT ME_StreamIn(ME_TextEditor *editor, DWORD format, EDITSTREAM *stream, BOOL stripLastCR)
{
  RTF_Info parser;
  ME_Style *style;
  int from, to, nUndoMode;
  int nEventMask = editor->nEventMask;
  ME_InStream inStream;
  BOOL invalidRTF = FALSE;
  ME_Cursor *selStart, *selEnd;
  LRESULT num_read = 0; /* bytes read for SF_TEXT, non-control chars inserted for SF_RTF */

  TRACE("stream==%p editor==%p format==0x%X\n", stream, editor, format);
  editor->nEventMask = 0;

  ME_GetSelectionOfs(editor, &from, &to);
  if (format & SFF_SELECTION && editor->mode & TM_RICHTEXT)
  {
    ME_GetSelection(editor, &selStart, &selEnd);
    style = ME_GetSelectionInsertStyle(editor);

    ME_InternalDeleteText(editor, selStart, to - from, FALSE);

    /* Don't insert text at the end of the table row */
    if (!editor->bEmulateVersion10) { /* v4.1 */
      ME_DisplayItem *para = editor->pCursors->pPara;
      if (para->member.para.nFlags & MEPF_ROWEND)
      {
        para = para->member.para.next_para;
        editor->pCursors[0].pPara = para;
        editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
        editor->pCursors[0].nOffset = 0;
      }
      if (para->member.para.nFlags & MEPF_ROWSTART)
      {
        para = para->member.para.next_para;
        editor->pCursors[0].pPara = para;
        editor->pCursors[0].pRun = ME_FindItemFwd(para, diRun);
        editor->pCursors[0].nOffset = 0;
      }
      editor->pCursors[1] = editor->pCursors[0];
    } else { /* v1.0 - 3.0 */
      if (editor->pCursors[0].pRun->member.run.nFlags & MERF_ENDPARA &&
          ME_IsInTable(editor->pCursors[0].pRun))
        return 0;
    }
  } else {
    style = editor->pBuffer->pDefaultStyle;
    ME_AddRefStyle(style);
    ME_SetSelection(editor, 0, 0);
    ME_InternalDeleteText(editor, &editor->pCursors[1],
                          ME_GetTextLength(editor), FALSE);
    from = to = 0;
    ME_ClearTempStyle(editor);
    ME_SetDefaultParaFormat(editor, &editor->pCursors[0].pPara->member.para.fmt);
  }


  /* Back up undo mode to a local variable */
  nUndoMode = editor->nUndoMode;

  /* Only create an undo if SFF_SELECTION is set */
  if (!(format & SFF_SELECTION))
    editor->nUndoMode = umIgnore;

  inStream.editstream = stream;
  inStream.editstream->dwError = 0;
  inStream.dwSize = 0;
  inStream.dwUsed = 0;

  if (format & SF_RTF)
  {
    /* Check if it's really RTF, and if it is not, use plain text */
    ME_StreamInFill(&inStream);
    if (!inStream.editstream->dwError)
    {
      if ((!editor->bEmulateVersion10 && strncmp(inStream.buffer, "{\\rtf", 5) && strncmp(inStream.buffer, "{\\urtf", 6))
	|| (editor->bEmulateVersion10 && *inStream.buffer != '{'))
      {
        invalidRTF = TRUE;
        inStream.editstream->dwError = -16;
      }
    }
  }

  if (!invalidRTF && !inStream.editstream->dwError)
  {
    ME_Cursor start;
    from = ME_GetCursorOfs(&editor->pCursors[0]);
    if (format & SF_RTF) {

      /* setup the RTF parser */
      memset(&parser, 0, sizeof parser);
      RTFSetEditStream(&parser, &inStream);
      parser.rtfFormat = format&(SF_TEXT|SF_RTF);
      parser.editor = editor;
      parser.style = style;
      WriterInit(&parser);
      RTFInit(&parser);
      RTFSetReadHook(&parser, ME_RTFReadHook);
      RTFSetDestinationCallback(&parser, rtfShpPict, ME_RTFReadShpPictGroup);
      RTFSetDestinationCallback(&parser, rtfPict, ME_RTFReadPictGroup);
      RTFSetDestinationCallback(&parser, rtfObject, ME_RTFReadObjectGroup);
      RTFSetDestinationCallback(&parser, rtfParNumbering, ME_RTFReadParnumGroup);
      if (!parser.editor->bEmulateVersion10) /* v4.1 */
      {
        RTFSetDestinationCallback(&parser, rtfNoNestTables, RTFSkipGroup);
        RTFSetDestinationCallback(&parser, rtfNestTableProps, RTFReadGroup);
      }
      BeginFile(&parser);

      /* do the parsing */
      RTFRead(&parser);
      RTFFlushOutputBuffer(&parser);
      if (!editor->bEmulateVersion10) { /* v4.1 */
        if (parser.tableDef && parser.tableDef->tableRowStart &&
            (parser.nestingLevel > 0 || parser.canInheritInTbl))
        {
          /* Delete any incomplete table row at the end of the rich text. */
          int nOfs, nChars;
          ME_DisplayItem *para;

          parser.rtfMinor = rtfRow;
          /* Complete the table row before deleting it.
           * By doing it this way we will have the current paragraph format set
           * properly to reflect that is not in the complete table, and undo items
           * will be added for this change to the current paragraph format. */
          if (parser.nestingLevel > 0)
          {
            while (parser.nestingLevel > 1)
              ME_RTFSpecialCharHook(&parser); /* Decrements nestingLevel */
            para = parser.tableDef->tableRowStart;
            ME_RTFSpecialCharHook(&parser);
          } else {
            para = parser.tableDef->tableRowStart;
            ME_RTFSpecialCharHook(&parser);
            assert(para->member.para.nFlags & MEPF_ROWEND);
            para = para->member.para.next_para;
          }

          editor->pCursors[1].pPara = para;
          editor->pCursors[1].pRun = ME_FindItemFwd(para, diRun);
          editor->pCursors[1].nOffset = 0;
          nOfs = ME_GetCursorOfs(&editor->pCursors[1]);
          nChars = ME_GetCursorOfs(&editor->pCursors[0]) - nOfs;
          ME_InternalDeleteText(editor, &editor->pCursors[1], nChars, TRUE);
          if (parser.tableDef)
            parser.tableDef->tableRowStart = NULL;
        }
      }
      ME_CheckTablesForCorruption(editor);
      RTFDestroy(&parser);

      if (parser.stackTop > 0)
      {
        while (--parser.stackTop >= 0)
        {
          ME_ReleaseStyle(parser.style);
          parser.style = parser.stack[parser.stackTop].style;
        }
        if (!inStream.editstream->dwError)
          inStream.editstream->dwError = HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
      }

      /* Remove last line break, as mandated by tests. This is not affected by
         CR/LF counters, since RTF streaming presents only \para tokens, which
         are converted according to the standard rules: \r for 2.0, \r\n for 1.0
       */
      if (stripLastCR && !(format & SFF_SELECTION)) {
        int newto;
        ME_GetSelection(editor, &selStart, &selEnd);
        newto = ME_GetCursorOfs(selEnd);
        if (newto > to + (editor->bEmulateVersion10 ? 1 : 0)) {
          WCHAR lastchar[3] = {'\0', '\0'};
          int linebreakSize = editor->bEmulateVersion10 ? 2 : 1;
          ME_Cursor linebreakCursor = *selEnd, lastcharCursor = *selEnd;
          CHARFORMAT2W cf;

          /* Set the final eop to the char fmt of the last char */
          cf.cbSize = sizeof(cf);
          cf.dwMask = CFM_ALL2;
          ME_MoveCursorChars(editor, &lastcharCursor, -1, FALSE);
          ME_GetCharFormat(editor, &lastcharCursor, &linebreakCursor, &cf);
          ME_SetSelection(editor, newto, -1);
          ME_SetSelectionCharFormat(editor, &cf);
          ME_SetSelection(editor, newto, newto);

          ME_MoveCursorChars(editor, &linebreakCursor, -linebreakSize, FALSE);
          ME_GetTextW(editor, lastchar, 2, &linebreakCursor, linebreakSize, FALSE, FALSE);
          if (lastchar[0] == '\r' && (lastchar[1] == '\n' || lastchar[1] == '\0')) {
            ME_InternalDeleteText(editor, &linebreakCursor, linebreakSize, FALSE);
          }
        }
      }
      to = ME_GetCursorOfs(&editor->pCursors[0]);
      num_read = to - from;

      style = parser.style;
    }
    else if (format & SF_TEXT)
    {
      num_read = ME_StreamInText(editor, format, &inStream, style);
      to = ME_GetCursorOfs(&editor->pCursors[0]);
    }
    else
      ERR("EM_STREAMIN without SF_TEXT or SF_RTF\n");
    /* put the cursor at the top */
    if (!(format & SFF_SELECTION))
      ME_SetSelection(editor, 0, 0);
    ME_CursorFromCharOfs(editor, from, &start);
    ME_UpdateLinkAttribute(editor, &start, to - from);
  }

  /* Restore saved undo mode */
  editor->nUndoMode = nUndoMode;

  /* even if we didn't add an undo, we need to commit anything on the stack */
  ME_CommitUndo(editor);

  /* If SFF_SELECTION isn't set, delete any undos from before we started too */
  if (!(format & SFF_SELECTION))
    ME_EmptyUndoStack(editor);

  ME_ReleaseStyle(style);
  editor->nEventMask = nEventMask;
  ME_UpdateRepaint(editor, FALSE);
  if (!(format & SFF_SELECTION)) {
    ME_ClearTempStyle(editor);
  }
  ITextHost_TxShowCaret(editor->texthost, FALSE);
  ME_MoveCaret(editor);
  ITextHost_TxShowCaret(editor->texthost, TRUE);
  ME_SendSelChange(editor);
  ME_SendRequestResize(editor, FALSE);

  return num_read;
}