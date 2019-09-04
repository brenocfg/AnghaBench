#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* fatalError; void* error; int /*<<< orphan*/  warning; int /*<<< orphan*/  comment; int /*<<< orphan*/  processingInstruction; void* ignorableWhitespace; int /*<<< orphan*/  cdataBlock; void* characters; int /*<<< orphan*/  reference; int /*<<< orphan*/  endDocument; int /*<<< orphan*/  startDocument; int /*<<< orphan*/  setDocumentLocator; int /*<<< orphan*/  unparsedEntityDecl; int /*<<< orphan*/  notationDecl; int /*<<< orphan*/  elementDecl; int /*<<< orphan*/  attributeDecl; int /*<<< orphan*/  entityDecl; int /*<<< orphan*/  getParameterEntity; int /*<<< orphan*/  getEntity; int /*<<< orphan*/  resolveEntity; int /*<<< orphan*/  hasExternalSubset; int /*<<< orphan*/  hasInternalSubset; int /*<<< orphan*/  isStandalone; int /*<<< orphan*/  externalSubset; int /*<<< orphan*/  internalSubset; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * serror; int /*<<< orphan*/  endElementNs; int /*<<< orphan*/  startElementNs; int /*<<< orphan*/ * endElement; int /*<<< orphan*/ * startElement; } ;
typedef  TYPE_1__ xmlSAXHandler ;

/* Variables and functions */
 int /*<<< orphan*/  XML_SAX2_MAGIC ; 
 void* xmlParserError ; 
 int /*<<< orphan*/  xmlParserWarning ; 
 int /*<<< orphan*/  xmlSAX2AttributeDecl ; 
 int /*<<< orphan*/  xmlSAX2CDataBlock ; 
 void* xmlSAX2Characters ; 
 int /*<<< orphan*/  xmlSAX2Comment ; 
 int /*<<< orphan*/  xmlSAX2ElementDecl ; 
 int /*<<< orphan*/  xmlSAX2EndDocument ; 
 int /*<<< orphan*/  xmlSAX2EndElementNs ; 
 int /*<<< orphan*/  xmlSAX2EntityDecl ; 
 int /*<<< orphan*/  xmlSAX2ExternalSubset ; 
 int /*<<< orphan*/  xmlSAX2GetEntity ; 
 int /*<<< orphan*/  xmlSAX2GetParameterEntity ; 
 int /*<<< orphan*/  xmlSAX2HasExternalSubset ; 
 int /*<<< orphan*/  xmlSAX2HasInternalSubset ; 
 int /*<<< orphan*/  xmlSAX2InternalSubset ; 
 int /*<<< orphan*/  xmlSAX2IsStandalone ; 
 int /*<<< orphan*/  xmlSAX2NotationDecl ; 
 int /*<<< orphan*/  xmlSAX2ProcessingInstruction ; 
 int /*<<< orphan*/  xmlSAX2Reference ; 
 int /*<<< orphan*/  xmlSAX2ResolveEntity ; 
 int /*<<< orphan*/  xmlSAX2SetDocumentLocator ; 
 int /*<<< orphan*/  xmlSAX2StartDocument ; 
 int /*<<< orphan*/  xmlSAX2StartElementNs ; 
 int /*<<< orphan*/  xmlSAX2UnparsedEntityDecl ; 

int
xmlSAXVersion(xmlSAXHandler *hdlr, int version)
{
    if (hdlr == NULL) return(-1);
    if (version == 2) {
	hdlr->startElement = NULL;
	hdlr->endElement = NULL;
	hdlr->startElementNs = xmlSAX2StartElementNs;
	hdlr->endElementNs = xmlSAX2EndElementNs;
	hdlr->serror = NULL;
	hdlr->initialized = XML_SAX2_MAGIC;
#ifdef LIBXML_SAX1_ENABLED
    } else if (version == 1) {
	hdlr->startElement = xmlSAX2StartElement;
	hdlr->endElement = xmlSAX2EndElement;
	hdlr->initialized = 1;
#endif /* LIBXML_SAX1_ENABLED */
    } else
        return(-1);
    hdlr->internalSubset = xmlSAX2InternalSubset;
    hdlr->externalSubset = xmlSAX2ExternalSubset;
    hdlr->isStandalone = xmlSAX2IsStandalone;
    hdlr->hasInternalSubset = xmlSAX2HasInternalSubset;
    hdlr->hasExternalSubset = xmlSAX2HasExternalSubset;
    hdlr->resolveEntity = xmlSAX2ResolveEntity;
    hdlr->getEntity = xmlSAX2GetEntity;
    hdlr->getParameterEntity = xmlSAX2GetParameterEntity;
    hdlr->entityDecl = xmlSAX2EntityDecl;
    hdlr->attributeDecl = xmlSAX2AttributeDecl;
    hdlr->elementDecl = xmlSAX2ElementDecl;
    hdlr->notationDecl = xmlSAX2NotationDecl;
    hdlr->unparsedEntityDecl = xmlSAX2UnparsedEntityDecl;
    hdlr->setDocumentLocator = xmlSAX2SetDocumentLocator;
    hdlr->startDocument = xmlSAX2StartDocument;
    hdlr->endDocument = xmlSAX2EndDocument;
    hdlr->reference = xmlSAX2Reference;
    hdlr->characters = xmlSAX2Characters;
    hdlr->cdataBlock = xmlSAX2CDataBlock;
    hdlr->ignorableWhitespace = xmlSAX2Characters;
    hdlr->processingInstruction = xmlSAX2ProcessingInstruction;
    hdlr->comment = xmlSAX2Comment;
    hdlr->warning = xmlParserWarning;
    hdlr->error = xmlParserError;
    hdlr->fatalError = xmlParserError;

    return(0);
}