#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cbSoFar; char* pszLines; int cbLines; void* fBody; void* fHeader; int /*<<< orphan*/  cPreviewLines; int /*<<< orphan*/  dwPopId; } ;
struct TYPE_5__ {int state; char* response; void* valid_info; int /*<<< orphan*/  preview_lines; int /*<<< orphan*/  msgid; } ;
typedef  TYPE_1__ POP3Transport ;
typedef  TYPE_2__ POP3TOP ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 void* FALSE ; 
 void* STATE_DONE ; 
#define  STATE_MULTILINE 129 
#define  STATE_OK 128 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static HRESULT parse_top_response(POP3Transport *This, POP3TOP *top)
{
    switch (This->state)
    {
    case STATE_OK:
        top->fHeader = FALSE;
        top->fBody = FALSE;
        top->dwPopId = This->msgid;
        top->cPreviewLines = This->preview_lines;
        top->cbSoFar = 0;
        top->pszLines = This->response;
        top->cbLines = 0;

        This->state = STATE_MULTILINE;
        This->valid_info = FALSE;
        return S_OK;

    case STATE_MULTILINE:
    {
        int len;

        if (This->response[0] == '.' && !This->response[1])
        {
            top->cbLines = top->cbSoFar;
            This->state = STATE_DONE;
            return S_OK;
        }
        top->fHeader = TRUE;
        if (!This->response[0]) top->fBody = TRUE;

        len = strlen(This->response);
        top->cbSoFar += len;
        top->pszLines = This->response;
        top->cbLines = len;

        This->valid_info = TRUE;
        return S_OK;
    }

    default:
        WARN("parse error\n");
        This->state = STATE_DONE;
        return S_FALSE;
    }
}