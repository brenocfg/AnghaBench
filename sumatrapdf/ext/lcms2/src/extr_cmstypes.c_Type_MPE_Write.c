#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct _cms_typehandler_struct {int dummy; } ;
typedef  size_t cmsUInt32Number ;
typedef  size_t cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsTagTypeSignature ;
struct TYPE_24__ {int /*<<< orphan*/  (* WritePtr ) (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_4__*,TYPE_2__*,int) ;} ;
typedef  TYPE_1__ cmsTagTypeHandler ;
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  size_t cmsStageSignature ;
struct TYPE_25__ {size_t Type; struct TYPE_25__* Next; } ;
typedef  TYPE_2__ cmsStage ;
struct TYPE_26__ {TYPE_2__* Elements; } ;
typedef  TYPE_3__ cmsPipeline ;
struct TYPE_27__ {size_t (* Tell ) (int /*<<< orphan*/ ,TYPE_4__*) ;int /*<<< orphan*/  (* Seek ) (int /*<<< orphan*/ ,TYPE_4__*,size_t) ;} ;
typedef  TYPE_4__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_28__ {int /*<<< orphan*/  TagTypes; } ;
typedef  TYPE_5__ _cmsTagTypePluginChunkType ;
typedef  int /*<<< orphan*/  _cmsTagBase ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* GetHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPEPlugin ; 
 int /*<<< orphan*/  SupportedMPEtypes ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _cmsCalloc (int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ _cmsContextGetClientChunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  _cmsTagSignature2String (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsWriteAlignment (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  _cmsWriteUInt16Number (int /*<<< orphan*/ ,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  _cmsWriteUInt32Number (int /*<<< orphan*/ ,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 size_t cmsPipelineInputChannels (int /*<<< orphan*/ ,TYPE_3__*) ; 
 size_t cmsPipelineOutputChannels (int /*<<< orphan*/ ,TYPE_3__*) ; 
 size_t cmsPipelineStageCount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 
 size_t stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t stub2 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t stub3 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t stub4 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,struct _cms_typehandler_struct*,TYPE_4__*,TYPE_2__*,int) ; 
 size_t stub6 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 size_t stub7 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,TYPE_4__*,size_t) ; 

__attribute__((used)) static
cmsBool Type_MPE_Write(cmsContext ContextID, struct _cms_typehandler_struct* self, cmsIOHANDLER* io, void* Ptr, cmsUInt32Number nItems)
{
    cmsUInt32Number i, BaseOffset, DirectoryPos, CurrentPos;
    cmsUInt32Number inputChan, outputChan;
    cmsUInt32Number ElemCount;
    cmsUInt32Number *ElementOffsets = NULL, *ElementSizes = NULL, Before;
    cmsStageSignature ElementSig;
    cmsPipeline* Lut = (cmsPipeline*) Ptr;
    cmsStage* Elem = Lut ->Elements;
    cmsTagTypeHandler* TypeHandler;
    _cmsTagTypePluginChunkType* MPETypePluginChunk  = ( _cmsTagTypePluginChunkType*) _cmsContextGetClientChunk(ContextID, MPEPlugin);

    BaseOffset = io ->Tell(ContextID, io) - sizeof(_cmsTagBase);

    inputChan  = cmsPipelineInputChannels(ContextID, Lut);
    outputChan = cmsPipelineOutputChannels(ContextID, Lut);
    ElemCount  = cmsPipelineStageCount(ContextID, Lut);

    ElementOffsets = (cmsUInt32Number *) _cmsCalloc(ContextID, ElemCount, sizeof(cmsUInt32Number));
    if (ElementOffsets == NULL) goto Error;

    ElementSizes = (cmsUInt32Number *) _cmsCalloc(ContextID, ElemCount, sizeof(cmsUInt32Number));
    if (ElementSizes == NULL) goto Error;

    // Write the head
    if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) inputChan)) goto Error;
    if (!_cmsWriteUInt16Number(ContextID, io, (cmsUInt16Number) outputChan)) goto Error;
    if (!_cmsWriteUInt32Number(ContextID, io, (cmsUInt16Number) ElemCount)) goto Error;

    DirectoryPos = io ->Tell(ContextID, io);

    // Write a fake directory to be filled latter on
    for (i=0; i < ElemCount; i++) {
        if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;  // Offset
        if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;  // size
    }

    // Write each single tag. Keep track of the size as well.
    for (i=0; i < ElemCount; i++) {

        ElementOffsets[i] = io ->Tell(ContextID, io) - BaseOffset;

        ElementSig = Elem ->Type;

        TypeHandler = GetHandler((cmsTagTypeSignature) ElementSig, MPETypePluginChunk->TagTypes, SupportedMPEtypes);
        if (TypeHandler == NULL)  {

                char String[5];

                _cmsTagSignature2String(String, (cmsTagSignature) ElementSig);

                 // An unknown element was found.
                 cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Found unknown MPE type '%s'", String);
                 goto Error;
        }

        if (!_cmsWriteUInt32Number(ContextID, io, ElementSig)) goto Error;
        if (!_cmsWriteUInt32Number(ContextID, io, 0)) goto Error;
        Before = io ->Tell(ContextID, io);
        if (!TypeHandler ->WritePtr(ContextID, self, io, Elem, 1)) goto Error;
        if (!_cmsWriteAlignment(ContextID, io)) goto Error;

        ElementSizes[i] = io ->Tell(ContextID, io) - Before;

        Elem = Elem ->Next;
    }

    // Write the directory
    CurrentPos = io ->Tell(ContextID, io);

    if (!io ->Seek(ContextID, io, DirectoryPos)) goto Error;

    for (i=0; i < ElemCount; i++) {
        if (!_cmsWriteUInt32Number(ContextID, io, ElementOffsets[i])) goto Error;
        if (!_cmsWriteUInt32Number(ContextID, io, ElementSizes[i])) goto Error;
    }

    if (!io ->Seek(ContextID, io, CurrentPos)) goto Error;

    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return TRUE;

Error:
    if (ElementOffsets != NULL) _cmsFree(ContextID, ElementOffsets);
    if (ElementSizes != NULL) _cmsFree(ContextID, ElementSizes);
    return FALSE;

    cmsUNUSED_PARAMETER(nItems);
}