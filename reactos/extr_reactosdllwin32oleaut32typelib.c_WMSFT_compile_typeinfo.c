#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_27__ {TYPE_2__ name_seg; } ;
typedef  TYPE_8__ WMSFT_TLBFile ;
struct TYPE_28__ {int typekind; int res4; int cElement; int posguid; int flags; int NameOffset; int version; int docstringoffs; scalar_t__ cImplTypes; int datatype1; int datatype2; int res19; scalar_t__ res18; int /*<<< orphan*/  size; int /*<<< orphan*/  cbSizeVft; int /*<<< orphan*/  oCustData; int /*<<< orphan*/  helpcontext; int /*<<< orphan*/  helpstringcontext; scalar_t__ resA; scalar_t__ res9; scalar_t__ res8; scalar_t__ res7; scalar_t__ res5; scalar_t__ res3; scalar_t__ res2; int /*<<< orphan*/  memoffset; } ;
struct TYPE_26__ {int hRef; } ;
struct TYPE_25__ {int wTypeFlags; int typekind; int cbAlignment; int cVars; int cFuncs; int wMinorVerNum; int wMajorVerNum; scalar_t__ cImplTypes; int /*<<< orphan*/  cbSizeInstance; int /*<<< orphan*/  cbSizeVft; } ;
struct TYPE_24__ {int offset; } ;
struct TYPE_23__ {int offset; } ;
struct TYPE_22__ {int offset; } ;
struct TYPE_20__ {int offset; } ;
struct TYPE_19__ {TYPE_7__* impltypes; TYPE_6__ typeattr; TYPE_5__* DllName; int /*<<< orphan*/  tdescAlias; int /*<<< orphan*/  pcustdata_list; int /*<<< orphan*/  dwHelpContext; int /*<<< orphan*/  dwHelpStringContext; TYPE_4__* DocString; int /*<<< orphan*/  hreftype; TYPE_3__* Name; TYPE_1__* guid; } ;
typedef  TYPE_9__ MSFT_TypeInfoBase ;
typedef  TYPE_10__ ITypeInfoImpl ;
typedef  int INT16 ;
typedef  int /*<<< orphan*/  HREFTYPE ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ TKIND_ALIAS ; 
 scalar_t__ TKIND_COCLASS ; 
 int TKIND_DISPATCH ; 
 scalar_t__ TKIND_MODULE ; 
 int TYPEFLAG_FDUAL ; 
 int WMSFT_append_typedesc (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMSFT_compile_custdata (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  WMSFT_compile_typeinfo_aux (TYPE_10__*,TYPE_8__*) ; 
 int WMSFT_compile_typeinfo_ref (TYPE_10__*,TYPE_8__*) ; 

__attribute__((used)) static DWORD WMSFT_compile_typeinfo(ITypeInfoImpl *info, INT16 index, WMSFT_TLBFile *file, char *data)
{
    DWORD size;

    size = sizeof(MSFT_TypeInfoBase);

    if(data){
        MSFT_TypeInfoBase *base = (MSFT_TypeInfoBase*)data;
        if(info->typeattr.wTypeFlags & TYPEFLAG_FDUAL)
            base->typekind = TKIND_DISPATCH;
        else
            base->typekind = info->typeattr.typekind;
        base->typekind |= index << 16; /* TODO: There are some other flags here */
        base->typekind |= (info->typeattr.cbAlignment << 11) | (info->typeattr.cbAlignment << 6);
        base->memoffset = WMSFT_compile_typeinfo_aux(info, file);
        base->res2 = 0;
        base->res3 = 0;
        base->res4 = 3;
        base->res5 = 0;
        base->cElement = (info->typeattr.cVars << 16) | info->typeattr.cFuncs;
        base->res7 = 0;
        base->res8 = 0;
        base->res9 = 0;
        base->resA = 0;
        if(info->guid)
            base->posguid = info->guid->offset;
        else
            base->posguid = -1;
        base->flags = info->typeattr.wTypeFlags;
        if(info->Name) {
            base->NameOffset = info->Name->offset;

            ((unsigned char*)file->name_seg.data)[info->Name->offset+9] = 0x38;
            *(HREFTYPE*)((unsigned char*)file->name_seg.data+info->Name->offset) = info->hreftype;
        }else {
            base->NameOffset = -1;
        }
        base->version = (info->typeattr.wMinorVerNum << 16) | info->typeattr.wMajorVerNum;
        if(info->DocString)
            base->docstringoffs = info->DocString->offset;
        else
            base->docstringoffs = -1;
        base->helpstringcontext = info->dwHelpStringContext;
        base->helpcontext = info->dwHelpContext;
        base->oCustData = WMSFT_compile_custdata(info->pcustdata_list, file);
        base->cImplTypes = info->typeattr.cImplTypes;
        base->cbSizeVft = info->typeattr.cbSizeVft;
        base->size = info->typeattr.cbSizeInstance;
        if(info->typeattr.typekind == TKIND_COCLASS){
            base->datatype1 = WMSFT_compile_typeinfo_ref(info, file);
        }else if(info->typeattr.typekind == TKIND_ALIAS){
            base->datatype1 = WMSFT_append_typedesc(info->tdescAlias, file, NULL, NULL);
        }else if(info->typeattr.typekind == TKIND_MODULE){
            if(info->DllName)
                base->datatype1 = info->DllName->offset;
            else
                base->datatype1 = -1;
        }else{
            if(info->typeattr.cImplTypes > 0)
                base->datatype1 = info->impltypes[0].hRef;
            else
                base->datatype1 = -1;
        }
        base->datatype2 = index; /* FIXME: i think there's more here */
        base->res18 = 0;
        base->res19 = -1;
    }

    return size;
}