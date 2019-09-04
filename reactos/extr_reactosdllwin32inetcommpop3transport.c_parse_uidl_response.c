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
struct TYPE_6__ {int state; char* ptr; char* response; void* valid_info; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {char* pszUidl; scalar_t__ dwPopId; } ;
typedef  TYPE_1__ POP3UIDL ;
typedef  TYPE_2__ POP3Transport ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  POP3CMD_GET_POPID ; 
 void* STATE_DONE ; 
#define  STATE_MULTILINE 129 
#define  STATE_OK 128 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  sscanf (char*,char*,scalar_t__*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static HRESULT parse_uidl_response(POP3Transport *This, POP3UIDL *uidl)
{
    char *p;

    uidl->dwPopId = 0;
    uidl->pszUidl = NULL;
    switch (This->state)
    {
    case STATE_OK:
        if (This->type == POP3CMD_GET_POPID)
        {
            if ((p = strchr(This->ptr, ' ')))
            {
                while (*p == ' ') p++;
                sscanf(p, "%u", &uidl->dwPopId);
                if ((p = strchr(p, ' ')))
                {
                    while (*p == ' ') p++;
                    uidl->pszUidl = p;
                    This->valid_info = TRUE;
                }
             }
             This->state = STATE_DONE;
             return S_OK;
        }
        This->state = STATE_MULTILINE;
        return S_OK;

    case STATE_MULTILINE:
        if (This->response[0] == '.' && !This->response[1])
        {
            This->valid_info = FALSE;
            This->state = STATE_DONE;
            return S_OK;
        }
        sscanf(This->response, "%u", &uidl->dwPopId);
        if ((p = strchr(This->response, ' ')))
        {
            while (*p == ' ') p++;
            uidl->pszUidl = p;
            This->valid_info = TRUE;
            return S_OK;
        }

    default:
        WARN("parse error\n");
        This->state = STATE_DONE;
        return S_FALSE;
    }
}