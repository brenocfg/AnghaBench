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
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int style; scalar_t__ line_count; scalar_t__ text; } ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ EDITSTATE ;

/* Variables and functions */
 scalar_t__ EDIT_EM_LineIndex (TYPE_1__*,scalar_t__) ; 
 scalar_t__ EDIT_EM_LineLength (TYPE_1__*,scalar_t__) ; 
 int ES_MULTILINE ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static INT EDIT_EM_GetLine(EDITSTATE *es, INT line, LPWSTR dst)
{
    INT line_len, dst_len;
    LPWSTR src;
    INT i;

    if (es->style & ES_MULTILINE)
    {
        if (line >= es->line_count)
            return 0;
    }
    else
        line = 0;

    i = EDIT_EM_LineIndex(es, line);
    src = es->text + i;
    line_len = EDIT_EM_LineLength(es, i);
    dst_len = *(WORD *)dst;

    if (dst_len <= line_len)
    {
        memcpy(dst, src, dst_len * sizeof(WCHAR));
        return dst_len;
    }
    else /* Append 0 if enough space */
    {
        memcpy(dst, src, line_len * sizeof(WCHAR));
        dst[line_len] = 0;
        return line_len;
    }
}