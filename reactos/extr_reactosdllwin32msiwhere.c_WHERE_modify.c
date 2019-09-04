#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int UINT ;
struct TYPE_10__ {TYPE_1__* ops; } ;
struct TYPE_9__ {TYPE_4__* view; int /*<<< orphan*/  next; } ;
struct TYPE_8__ {TYPE_3__* tables; } ;
struct TYPE_7__ {int (* modify ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int /*<<< orphan*/  MSIMODIFY ;
typedef  TYPE_3__ JOINTABLE ;

/* Variables and functions */
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
#define  MSIMODIFY_ASSIGN 140 
#define  MSIMODIFY_DELETE 139 
#define  MSIMODIFY_INSERT 138 
#define  MSIMODIFY_INSERT_TEMPORARY 137 
#define  MSIMODIFY_MERGE 136 
#define  MSIMODIFY_REFRESH 135 
#define  MSIMODIFY_REPLACE 134 
#define  MSIMODIFY_SEEK 133 
#define  MSIMODIFY_UPDATE 132 
#define  MSIMODIFY_VALIDATE 131 
#define  MSIMODIFY_VALIDATE_DELETE 130 
#define  MSIMODIFY_VALIDATE_FIELD 129 
#define  MSIMODIFY_VALIDATE_NEW 128 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,struct tagMSIVIEW*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ find_row (TYPE_2__*,int,int**) ; 
 int join_modify_update (struct tagMSIVIEW*,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static UINT WHERE_modify( struct tagMSIVIEW *view, MSIMODIFY eModifyMode,
                          MSIRECORD *rec, UINT row )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    JOINTABLE *table = wv->tables;
    UINT r;

    TRACE("%p %d %p\n", wv, eModifyMode, rec);

    if (!table)
        return ERROR_FUNCTION_FAILED;

    if (!table->next)
    {
        UINT *rows;

        if (find_row(wv, row - 1, &rows) == ERROR_SUCCESS)
            row = rows[0] + 1;
        else
            row = -1;

        return table->view->ops->modify(table->view, eModifyMode, rec, row);
    }

    switch (eModifyMode)
    {
    case MSIMODIFY_UPDATE:
        return join_modify_update( view, rec );

    case MSIMODIFY_ASSIGN:
    case MSIMODIFY_DELETE:
    case MSIMODIFY_INSERT:
    case MSIMODIFY_INSERT_TEMPORARY:
    case MSIMODIFY_MERGE:
    case MSIMODIFY_REPLACE:
    case MSIMODIFY_SEEK:
    case MSIMODIFY_VALIDATE:
    case MSIMODIFY_VALIDATE_DELETE:
    case MSIMODIFY_VALIDATE_FIELD:
    case MSIMODIFY_VALIDATE_NEW:
        r = ERROR_FUNCTION_FAILED;
        break;

    case MSIMODIFY_REFRESH:
        r = ERROR_CALL_NOT_IMPLEMENTED;
        break;

    default:
        WARN("%p %d %p %u - unknown mode\n", view, eModifyMode, rec, row );
        r = ERROR_INVALID_PARAMETER;
        break;
    }

    return r;
}