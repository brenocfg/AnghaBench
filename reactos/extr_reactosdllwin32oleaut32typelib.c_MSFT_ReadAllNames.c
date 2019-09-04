#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_17__ {int namelen; } ;
struct TYPE_16__ {TYPE_3__* pLibInfo; TYPE_2__* pTblDir; } ;
struct TYPE_15__ {int offset; int /*<<< orphan*/  entry; int /*<<< orphan*/ * str; } ;
struct TYPE_14__ {int /*<<< orphan*/  name_list; } ;
struct TYPE_12__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_13__ {TYPE_1__ pNametab; } ;
typedef  TYPE_4__ TLBString ;
typedef  TYPE_5__ TLBContext ;
typedef  TYPE_6__ MSFT_NameIntro ;
typedef  int INT16 ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  DO_NOT_SEEK ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 int MB_ERR_INVALID_CHARS ; 
 int MB_PRECOMPOSED ; 
 int /*<<< orphan*/  MSFT_Read (char*,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSFT_ReadLEWords (TYPE_6__*,int,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSFT_Seek (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocStringByteLen (int /*<<< orphan*/ *,int) ; 
 void* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT MSFT_ReadAllNames(TLBContext *pcx)
{
    char *string;
    MSFT_NameIntro intro;
    INT16 len_piece;
    int offs = 0, lengthInChars;

    MSFT_Seek(pcx, pcx->pTblDir->pNametab.offset);
    while (1) {
        TLBString *tlbstr;

        if (offs >= pcx->pTblDir->pNametab.length)
            return S_OK;

        MSFT_ReadLEWords(&intro, sizeof(MSFT_NameIntro), pcx, DO_NOT_SEEK);
        intro.namelen &= 0xFF;
        len_piece = intro.namelen + sizeof(MSFT_NameIntro);
        if(len_piece % 4)
            len_piece = (len_piece + 4) & ~0x3;
        if(len_piece < 8)
            len_piece = 8;

        string = heap_alloc(len_piece + 1);
        MSFT_Read(string, len_piece - sizeof(MSFT_NameIntro), pcx, DO_NOT_SEEK);
        string[intro.namelen] = '\0';

        lengthInChars = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                                            string, -1, NULL, 0);
        if (!lengthInChars) {
            heap_free(string);
            return E_UNEXPECTED;
        }

        tlbstr = heap_alloc(sizeof(TLBString));

        tlbstr->offset = offs;
        tlbstr->str = SysAllocStringByteLen(NULL, lengthInChars * sizeof(WCHAR));
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, string, -1, tlbstr->str, lengthInChars);

        heap_free(string);

        list_add_tail(&pcx->pLibInfo->name_list, &tlbstr->entry);

        offs += len_piece;
    }
}