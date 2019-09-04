#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_9__ ;
typedef  struct TYPE_56__   TYPE_8__ ;
typedef  struct TYPE_55__   TYPE_7__ ;
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_25__ ;
typedef  struct TYPE_48__   TYPE_24__ ;
typedef  struct TYPE_47__   TYPE_23__ ;
typedef  struct TYPE_46__   TYPE_22__ ;
typedef  struct TYPE_45__   TYPE_21__ ;
typedef  struct TYPE_44__   TYPE_20__ ;
typedef  struct TYPE_43__   TYPE_1__ ;
typedef  struct TYPE_42__   TYPE_19__ ;
typedef  struct TYPE_41__   TYPE_18__ ;
typedef  struct TYPE_40__   TYPE_17__ ;
typedef  struct TYPE_39__   TYPE_16__ ;
typedef  struct TYPE_38__   TYPE_15__ ;
typedef  struct TYPE_37__   TYPE_14__ ;
typedef  struct TYPE_36__   TYPE_13__ ;
typedef  struct TYPE_35__   TYPE_12__ ;
typedef  struct TYPE_34__   TYPE_11__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
struct TYPE_41__ {size_t len; scalar_t__ data; } ;
struct TYPE_40__ {TYPE_18__ aux_seg; } ;
typedef  TYPE_17__ WMSFT_TLBFile ;
typedef  TYPE_18__ WMSFT_SegContents ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  size_t UINT ;
struct TYPE_57__ {int /*<<< orphan*/  tdesc; } ;
struct TYPE_54__ {int wParamFlags; TYPE_5__* pparamdescex; } ;
struct TYPE_55__ {TYPE_6__ paramdesc; } ;
struct TYPE_56__ {TYPE_7__ u; int /*<<< orphan*/  tdesc; } ;
struct TYPE_53__ {int /*<<< orphan*/  varDefaultValue; } ;
struct TYPE_52__ {TYPE_3__* Name; } ;
struct TYPE_51__ {int offset; } ;
struct TYPE_50__ {int offset; } ;
struct TYPE_38__ {size_t cFuncs; size_t cVars; } ;
struct TYPE_49__ {TYPE_19__* vardescs; TYPE_15__ typeattr; TYPE_21__* funcdescs; } ;
struct TYPE_48__ {int funcdescsize; int FKCCIC; int nrargs; int oHelpString; int oEntry; int res9; int resA; scalar_t__ HelpStringContext; size_t Info; scalar_t__ HelpContext; void* oCustData; int /*<<< orphan*/  nroargs; int /*<<< orphan*/  VtableOffset; int /*<<< orphan*/  Flags; void* DataType; } ;
struct TYPE_47__ {int oName; int Flags; void* DataType; } ;
struct TYPE_46__ {int vardescsize; scalar_t__ VarKind; scalar_t__ HelpContext; int HelpString; int res9; scalar_t__ HelpStringContext; size_t Info; void* oCustData; void* OffsValue; int /*<<< orphan*/  Flags; void* DataType; } ;
struct TYPE_43__ {int /*<<< orphan*/  tdesc; } ;
struct TYPE_35__ {int cParams; int funckind; int invkind; int callconv; int /*<<< orphan*/  memid; TYPE_8__* lprgelemdescParam; int /*<<< orphan*/  cParamsOpt; int /*<<< orphan*/  oVft; int /*<<< orphan*/  wFuncFlags; TYPE_1__ elemdescFunc; } ;
struct TYPE_45__ {scalar_t__ HelpStringContext; TYPE_14__* Name; TYPE_12__ funcdesc; TYPE_4__* pParamDesc; scalar_t__ helpcontext; TYPE_2__* HelpString; TYPE_20__* Entry; int /*<<< orphan*/  custdata_list; } ;
struct TYPE_44__ {int offset; } ;
struct TYPE_33__ {void* oInst; int /*<<< orphan*/ * lpvarValue; } ;
struct TYPE_36__ {scalar_t__ varkind; int /*<<< orphan*/  memid; TYPE_10__ u; int /*<<< orphan*/  wVarFlags; TYPE_9__ elemdescVar; } ;
struct TYPE_42__ {scalar_t__ HelpStringContext; scalar_t__ HelpContext; TYPE_16__* Name; TYPE_13__ vardesc; TYPE_11__* HelpString; int /*<<< orphan*/  custdata_list; } ;
struct TYPE_39__ {size_t offset; } ;
struct TYPE_37__ {size_t offset; } ;
struct TYPE_34__ {int offset; } ;
typedef  TYPE_19__ TLBVarDesc ;
typedef  TYPE_20__ TLBString ;
typedef  TYPE_21__ TLBFuncDesc ;
typedef  int /*<<< orphan*/  PARAMDESCEX ;
typedef  TYPE_22__ MSFT_VarRecord ;
typedef  TYPE_23__ MSFT_ParameterInfo ;
typedef  TYPE_24__ MSFT_FuncRecord ;
typedef  int /*<<< orphan*/  MEMBERID ;
typedef  TYPE_25__ ITypeInfoImpl ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  ELEMDESC ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ IS_INTRESOURCE (TYPE_20__*) ; 
 void* LOWORD (TYPE_20__*) ; 
 int PARAMFLAG_FHASDEFAULT ; 
 scalar_t__ VAR_CONST ; 
 void* WMSFT_append_typedesc (int /*<<< orphan*/ *,TYPE_17__*,int /*<<< orphan*/ *,int*) ; 
 void* WMSFT_compile_custdata (int /*<<< orphan*/ *,TYPE_17__*) ; 
 void* WMSFT_encode_variant (int /*<<< orphan*/ *,TYPE_17__*) ; 
 scalar_t__ heap_alloc (int) ; 
 scalar_t__ heap_realloc (scalar_t__,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static DWORD WMSFT_compile_typeinfo_aux(ITypeInfoImpl *info,
        WMSFT_TLBFile *file)
{
    WMSFT_SegContents *aux_seg = &file->aux_seg;
    DWORD ret = aux_seg->len, i, j, recorded_size = 0, extra_size = 0;
    MSFT_VarRecord *varrecord;
    MSFT_FuncRecord *funcrecord;
    MEMBERID *memid;
    DWORD *name, *offsets, offs;

    for(i = 0; i < info->typeattr.cFuncs; ++i){
        TLBFuncDesc *desc = &info->funcdescs[i];

        recorded_size += 6 * sizeof(INT); /* mandatory fields */

        /* optional fields */
        /* TODO: oArgCustData - FuncSetCustData not impl yet */
        if(!list_empty(&desc->custdata_list))
            recorded_size += 7 * sizeof(INT);
        else if(desc->HelpStringContext != 0)
            recorded_size += 6 * sizeof(INT);
        /* res9? resA? */
        else if(desc->Entry)
            recorded_size += 3 * sizeof(INT);
        else if(desc->HelpString)
            recorded_size += 2 * sizeof(INT);
        else if(desc->helpcontext)
            recorded_size += sizeof(INT);

        recorded_size += desc->funcdesc.cParams * sizeof(MSFT_ParameterInfo);

        for(j = 0; j < desc->funcdesc.cParams; ++j){
            if(desc->funcdesc.lprgelemdescParam[j].u.paramdesc.wParamFlags & PARAMFLAG_FHASDEFAULT){
                recorded_size += desc->funcdesc.cParams * sizeof(INT);
                break;
            }
        }

        extra_size += 2 * sizeof(INT); /* memberid, name offs */
    }

    for(i = 0; i < info->typeattr.cVars; ++i){
        TLBVarDesc *desc = &info->vardescs[i];

        recorded_size += 5 * sizeof(INT); /* mandatory fields */

        /* optional fields */
        if(desc->HelpStringContext != 0)
            recorded_size += 5 * sizeof(INT);
        else if(!list_empty(&desc->custdata_list))
            recorded_size += 4 * sizeof(INT);
        /* res9? */
        else if(desc->HelpString)
            recorded_size += 2 * sizeof(INT);
        else if(desc->HelpContext != 0)
            recorded_size += sizeof(INT);

        extra_size += 2 * sizeof(INT); /* memberid, name offs */
    }

    if(!recorded_size && !extra_size)
        return ret;

    extra_size += sizeof(INT); /* total aux size for this typeinfo */

    aux_seg->len += recorded_size + extra_size;

    aux_seg->len += sizeof(INT) * (info->typeattr.cVars + info->typeattr.cFuncs); /* offsets at the end */

    if(aux_seg->data)
        aux_seg->data = heap_realloc(aux_seg->data, aux_seg->len);
    else
        aux_seg->data = heap_alloc(aux_seg->len);

    *((DWORD*)((char *)aux_seg->data + ret)) = recorded_size;

    offsets = (DWORD*)((char *)aux_seg->data + ret + recorded_size + extra_size);
    offs = 0;

    funcrecord = (MSFT_FuncRecord*)(((char *)aux_seg->data) + ret + sizeof(INT));
    for(i = 0; i < info->typeattr.cFuncs; ++i){
        TLBFuncDesc *desc = &info->funcdescs[i];
        DWORD size = 6 * sizeof(INT), paramdefault_size = 0, *paramdefault;

        funcrecord->funcdescsize = sizeof(desc->funcdesc) + desc->funcdesc.cParams * sizeof(ELEMDESC);
        funcrecord->DataType = WMSFT_append_typedesc(&desc->funcdesc.elemdescFunc.tdesc, file, NULL, &funcrecord->funcdescsize);
        funcrecord->Flags = desc->funcdesc.wFuncFlags;
        funcrecord->VtableOffset = desc->funcdesc.oVft;

        /* FKCCIC:
         * XXXX XXXX XXXX XXXX  XXXX XXXX XXXX XXXX
         *                                      ^^^funckind
         *                                 ^^^ ^invkind
         *                                ^has_cust_data
         *                           ^^^^callconv
         *                         ^has_param_defaults
         *                        ^oEntry_is_intresource
         */
        funcrecord->FKCCIC =
            desc->funcdesc.funckind |
            (desc->funcdesc.invkind << 3) |
            (list_empty(&desc->custdata_list) ? 0 : 0x80) |
            (desc->funcdesc.callconv << 8);

        if(desc->Entry && desc->Entry != (TLBString*)-1 && IS_INTRESOURCE(desc->Entry))
            funcrecord->FKCCIC |= 0x2000;

        for(j = 0; j < desc->funcdesc.cParams; ++j){
            if(desc->funcdesc.lprgelemdescParam[j].u.paramdesc.wParamFlags & PARAMFLAG_FHASDEFAULT){
                paramdefault_size = sizeof(INT) * desc->funcdesc.cParams;
                funcrecord->funcdescsize += sizeof(PARAMDESCEX);
            }
        }
        if(paramdefault_size > 0)
            funcrecord->FKCCIC |= 0x1000;

        funcrecord->nrargs = desc->funcdesc.cParams;
        funcrecord->nroargs = desc->funcdesc.cParamsOpt;

        /* optional fields */
        /* res9? resA? */
        if(!list_empty(&desc->custdata_list)){
            size += 7 * sizeof(INT);
            funcrecord->HelpContext = desc->helpcontext;
            if(desc->HelpString)
                funcrecord->oHelpString = desc->HelpString->offset;
            else
                funcrecord->oHelpString = -1;
            if(!desc->Entry)
                funcrecord->oEntry = -1;
            else if(IS_INTRESOURCE(desc->Entry))
                funcrecord->oEntry = LOWORD(desc->Entry);
            else
                funcrecord->oEntry = desc->Entry->offset;
            funcrecord->res9 = -1;
            funcrecord->resA = -1;
            funcrecord->HelpStringContext = desc->HelpStringContext;
            funcrecord->oCustData = WMSFT_compile_custdata(&desc->custdata_list, file);
        }else if(desc->HelpStringContext != 0){
            size += 6 * sizeof(INT);
            funcrecord->HelpContext = desc->helpcontext;
            if(desc->HelpString)
                funcrecord->oHelpString = desc->HelpString->offset;
            else
                funcrecord->oHelpString = -1;
            if(!desc->Entry)
                funcrecord->oEntry = -1;
            else if(IS_INTRESOURCE(desc->Entry))
                funcrecord->oEntry = LOWORD(desc->Entry);
            else
                funcrecord->oEntry = desc->Entry->offset;
            funcrecord->res9 = -1;
            funcrecord->resA = -1;
            funcrecord->HelpStringContext = desc->HelpStringContext;
        }else if(desc->Entry){
            size += 3 * sizeof(INT);
            funcrecord->HelpContext = desc->helpcontext;
            if(desc->HelpString)
                funcrecord->oHelpString = desc->HelpString->offset;
            else
                funcrecord->oHelpString = -1;
            if(!desc->Entry)
                funcrecord->oEntry = -1;
            else if(IS_INTRESOURCE(desc->Entry))
                funcrecord->oEntry = LOWORD(desc->Entry);
            else
                funcrecord->oEntry = desc->Entry->offset;
        }else if(desc->HelpString){
            size += 2 * sizeof(INT);
            funcrecord->HelpContext = desc->helpcontext;
            funcrecord->oHelpString = desc->HelpString->offset;
        }else if(desc->helpcontext){
            size += sizeof(INT);
            funcrecord->HelpContext = desc->helpcontext;
        }

        paramdefault = (DWORD*)((char *)funcrecord + size);
        size += paramdefault_size;

        for(j = 0; j < desc->funcdesc.cParams; ++j){
            MSFT_ParameterInfo *info = (MSFT_ParameterInfo*)(((char *)funcrecord) + size);

            info->DataType = WMSFT_append_typedesc(&desc->funcdesc.lprgelemdescParam[j].tdesc, file, NULL, &funcrecord->funcdescsize);
            if(desc->pParamDesc[j].Name)
                info->oName = desc->pParamDesc[j].Name->offset;
            else
                info->oName = -1;
            info->Flags = desc->funcdesc.lprgelemdescParam[j].u.paramdesc.wParamFlags;

            if(paramdefault_size){
                if(desc->funcdesc.lprgelemdescParam[j].u.paramdesc.wParamFlags & PARAMFLAG_FHASDEFAULT)
                    *paramdefault = WMSFT_encode_variant(&desc->funcdesc.lprgelemdescParam[j].u.paramdesc.pparamdescex->varDefaultValue, file);
                else if(paramdefault_size)
                    *paramdefault = -1;
                ++paramdefault;
            }

            size += sizeof(MSFT_ParameterInfo);
        }

        funcrecord->Info = size | (i << 16); /* is it just the index? */

        *offsets = offs;
        offs += size;
        ++offsets;

        funcrecord = (MSFT_FuncRecord*)(((char*)funcrecord) + size);
    }

    varrecord = (MSFT_VarRecord*)funcrecord;
    for(i = 0; i < info->typeattr.cVars; ++i){
        TLBVarDesc *desc = &info->vardescs[i];
        DWORD size = 5 * sizeof(INT);

        varrecord->vardescsize = sizeof(desc->vardesc);
        varrecord->DataType = WMSFT_append_typedesc(&desc->vardesc.elemdescVar.tdesc, file, NULL, &varrecord->vardescsize);
        varrecord->Flags = desc->vardesc.wVarFlags;
        varrecord->VarKind = desc->vardesc.varkind;

        if(desc->vardesc.varkind == VAR_CONST){
            varrecord->vardescsize += sizeof(VARIANT);
            varrecord->OffsValue = WMSFT_encode_variant(desc->vardesc.u.lpvarValue, file);
        }else
            varrecord->OffsValue = desc->vardesc.u.oInst;

        /* res9? */
        if(desc->HelpStringContext != 0){
            size += 5 * sizeof(INT);
            varrecord->HelpContext = desc->HelpContext;
            if(desc->HelpString)
                varrecord->HelpString = desc->HelpString->offset;
            else
                varrecord->HelpString = -1;
            varrecord->res9 = -1;
            varrecord->oCustData = WMSFT_compile_custdata(&desc->custdata_list, file);
            varrecord->HelpStringContext = desc->HelpStringContext;
        }else if(!list_empty(&desc->custdata_list)){
            size += 4 * sizeof(INT);
            varrecord->HelpContext = desc->HelpContext;
            if(desc->HelpString)
                varrecord->HelpString = desc->HelpString->offset;
            else
                varrecord->HelpString = -1;
            varrecord->res9 = -1;
            varrecord->oCustData = WMSFT_compile_custdata(&desc->custdata_list, file);
        }else if(desc->HelpString){
            size += 2 * sizeof(INT);
            varrecord->HelpContext = desc->HelpContext;
            if(desc->HelpString)
                varrecord->HelpString = desc->HelpString->offset;
            else
                varrecord->HelpString = -1;
        }else if(desc->HelpContext != 0){
            size += sizeof(INT);
            varrecord->HelpContext = desc->HelpContext;
        }

        varrecord->Info = size | (i << 16);

        *offsets = offs;
        offs += size;
        ++offsets;

        varrecord = (MSFT_VarRecord*)(((char*)varrecord) + size);
    }

    memid = (MEMBERID*)varrecord;
    for(i = 0; i < info->typeattr.cFuncs; ++i){
        TLBFuncDesc *desc = &info->funcdescs[i];
        *memid = desc->funcdesc.memid;
        ++memid;
    }
    for(i = 0; i < info->typeattr.cVars; ++i){
        TLBVarDesc *desc = &info->vardescs[i];
        *memid = desc->vardesc.memid;
        ++memid;
    }

    name = (UINT*)memid;
    for(i = 0; i < info->typeattr.cFuncs; ++i){
        TLBFuncDesc *desc = &info->funcdescs[i];
        if(desc->Name)
            *name = desc->Name->offset;
        else
            *name = -1;
        ++name;
    }
    for(i = 0; i < info->typeattr.cVars; ++i){
        TLBVarDesc *desc = &info->vardescs[i];
        if(desc->Name)
            *name = desc->Name->offset;
        else
            *name = -1;
        ++name;
    }

    return ret;
}