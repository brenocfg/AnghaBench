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
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  int MSIMODIFY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,struct tagMSIVIEW*,int,int /*<<< orphan*/ *) ; 
#define  MSIMODIFY_ASSIGN 139 
#define  MSIMODIFY_DELETE 138 
#define  MSIMODIFY_INSERT 137 
#define  MSIMODIFY_INSERT_TEMPORARY 136 
#define  MSIMODIFY_MERGE 135 
#define  MSIMODIFY_REFRESH 134 
#define  MSIMODIFY_REPLACE 133 
#define  MSIMODIFY_UPDATE 132 
#define  MSIMODIFY_VALIDATE 131 
#define  MSIMODIFY_VALIDATE_DELETE 130 
#define  MSIMODIFY_VALIDATE_FIELD 129 
#define  MSIMODIFY_VALIDATE_NEW 128 
 int /*<<< orphan*/  STORAGES_insert_row (struct tagMSIVIEW*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storages_modify_assign (struct tagMSIVIEW*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storages_modify_update (struct tagMSIVIEW*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT STORAGES_modify(struct tagMSIVIEW *view, MSIMODIFY eModifyMode, MSIRECORD *rec, UINT row)
{
    UINT r;

    TRACE("%p %d %p\n", view, eModifyMode, rec);

    switch (eModifyMode)
    {
    case MSIMODIFY_ASSIGN:
        r = storages_modify_assign(view, rec);
        break;

    case MSIMODIFY_INSERT:
        r = STORAGES_insert_row(view, rec, -1, FALSE);
        break;

    case MSIMODIFY_UPDATE:
        r = storages_modify_update(view, rec);
        break;

    case MSIMODIFY_VALIDATE_NEW:
    case MSIMODIFY_INSERT_TEMPORARY:
    case MSIMODIFY_REFRESH:
    case MSIMODIFY_REPLACE:
    case MSIMODIFY_MERGE:
    case MSIMODIFY_DELETE:
    case MSIMODIFY_VALIDATE:
    case MSIMODIFY_VALIDATE_FIELD:
    case MSIMODIFY_VALIDATE_DELETE:
        FIXME("%p %d %p - mode not implemented\n", view, eModifyMode, rec );
        r = ERROR_CALL_NOT_IMPLEMENTED;
        break;

    default:
        r = ERROR_INVALID_DATA;
    }

    return r;
}