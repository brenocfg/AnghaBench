#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlParserCtxtPtr ;
typedef  TYPE_2__* xmlEntityPtr ;
typedef  int xmlChar ;
struct TYPE_12__ {scalar_t__ etype; char* content; int* name; unsigned long checked; scalar_t__ owner; } ;
struct TYPE_11__ {scalar_t__ instate; int options; scalar_t__ replaceEntities; unsigned long nbentities; int /*<<< orphan*/  depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_BUF (int,int*,size_t,int) ; 
 int CUR_CHAR (int) ; 
 int /*<<< orphan*/  GROW ; 
 size_t INT_MAX ; 
 scalar_t__ IS_CHAR (int) ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  NEXTL (int) ; 
 char NXT (int) ; 
 char RAW ; 
 int /*<<< orphan*/  XML_ERR_ATTRIBUTE_NOT_FINISHED ; 
 int /*<<< orphan*/  XML_ERR_ATTRIBUTE_NOT_STARTED ; 
 int /*<<< orphan*/  XML_ERR_INVALID_CHAR ; 
 int /*<<< orphan*/  XML_ERR_LT_IN_ATTRIBUTE ; 
 scalar_t__ XML_INTERNAL_PREDEFINED_ENTITY ; 
 size_t XML_MAX_TEXT_LENGTH ; 
 void* XML_PARSER_ATTRIBUTE_VALUE ; 
 size_t XML_PARSER_BUFFER_SIZE ; 
 scalar_t__ XML_PARSER_EOF ; 
 int XML_PARSE_HUGE ; 
 int /*<<< orphan*/  XML_SUBSTITUTE_REF ; 
 int /*<<< orphan*/  growBuffer (int*,int) ; 
 scalar_t__ xmlCopyChar (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  xmlErrMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFatalErrMsg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlFree (int*) ; 
 scalar_t__ xmlMallocAtomic (size_t) ; 
 int xmlParseCharRef (TYPE_1__*) ; 
 TYPE_2__* xmlParseEntityRef (TYPE_1__*) ; 
 scalar_t__ xmlStrchr (int*,char) ; 
 int* xmlStringDecodeEntities (TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xmlStrlen (int*) ; 

__attribute__((used)) static xmlChar *
xmlParseAttValueComplex(xmlParserCtxtPtr ctxt, int *attlen, int normalize) {
    xmlChar limit = 0;
    xmlChar *buf = NULL;
    xmlChar *rep = NULL;
    size_t len = 0;
    size_t buf_size = 0;
    int c, l, in_space = 0;
    xmlChar *current = NULL;
    xmlEntityPtr ent;

    if (NXT(0) == '"') {
	ctxt->instate = XML_PARSER_ATTRIBUTE_VALUE;
	limit = '"';
        NEXT;
    } else if (NXT(0) == '\'') {
	limit = '\'';
	ctxt->instate = XML_PARSER_ATTRIBUTE_VALUE;
        NEXT;
    } else {
	xmlFatalErr(ctxt, XML_ERR_ATTRIBUTE_NOT_STARTED, NULL);
	return(NULL);
    }

    /*
     * allocate a translation buffer.
     */
    buf_size = XML_PARSER_BUFFER_SIZE;
    buf = (xmlChar *) xmlMallocAtomic(buf_size);
    if (buf == NULL) goto mem_error;

    /*
     * OK loop until we reach one of the ending char or a size limit.
     */
    c = CUR_CHAR(l);
    while (((NXT(0) != limit) && /* checked */
            (IS_CHAR(c)) && (c != '<')) &&
            (ctxt->instate != XML_PARSER_EOF)) {
        /*
         * Impose a reasonable limit on attribute size, unless XML_PARSE_HUGE
         * special option is given
         */
        if ((len > XML_MAX_TEXT_LENGTH) &&
            ((ctxt->options & XML_PARSE_HUGE) == 0)) {
            xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                           "AttValue length too long\n");
            goto mem_error;
        }
	if (c == 0) break;
	if (c == '&') {
	    in_space = 0;
	    if (NXT(1) == '#') {
		int val = xmlParseCharRef(ctxt);

		if (val == '&') {
		    if (ctxt->replaceEntities) {
			if (len + 10 > buf_size) {
			    growBuffer(buf, 10);
			}
			buf[len++] = '&';
		    } else {
			/*
			 * The reparsing will be done in xmlStringGetNodeList()
			 * called by the attribute() function in SAX.c
			 */
			if (len + 10 > buf_size) {
			    growBuffer(buf, 10);
			}
			buf[len++] = '&';
			buf[len++] = '#';
			buf[len++] = '3';
			buf[len++] = '8';
			buf[len++] = ';';
		    }
		} else if (val != 0) {
		    if (len + 10 > buf_size) {
			growBuffer(buf, 10);
		    }
		    len += xmlCopyChar(0, &buf[len], val);
		}
	    } else {
		ent = xmlParseEntityRef(ctxt);
		ctxt->nbentities++;
		if (ent != NULL)
		    ctxt->nbentities += ent->owner;
		if ((ent != NULL) &&
		    (ent->etype == XML_INTERNAL_PREDEFINED_ENTITY)) {
		    if (len + 10 > buf_size) {
			growBuffer(buf, 10);
		    }
		    if ((ctxt->replaceEntities == 0) &&
		        (ent->content[0] == '&')) {
			buf[len++] = '&';
			buf[len++] = '#';
			buf[len++] = '3';
			buf[len++] = '8';
			buf[len++] = ';';
		    } else {
			buf[len++] = ent->content[0];
		    }
		} else if ((ent != NULL) &&
		           (ctxt->replaceEntities != 0)) {
		    if (ent->etype != XML_INTERNAL_PREDEFINED_ENTITY) {
			++ctxt->depth;
			rep = xmlStringDecodeEntities(ctxt, ent->content,
						      XML_SUBSTITUTE_REF,
						      0, 0, 0);
			--ctxt->depth;
			if (rep != NULL) {
			    current = rep;
			    while (*current != 0) { /* non input consuming */
                                if ((*current == 0xD) || (*current == 0xA) ||
                                    (*current == 0x9)) {
                                    buf[len++] = 0x20;
                                    current++;
                                } else
                                    buf[len++] = *current++;
				if (len + 10 > buf_size) {
				    growBuffer(buf, 10);
				}
			    }
			    xmlFree(rep);
			    rep = NULL;
			}
		    } else {
			if (len + 10 > buf_size) {
			    growBuffer(buf, 10);
			}
			if (ent->content != NULL)
			    buf[len++] = ent->content[0];
		    }
		} else if (ent != NULL) {
		    int i = xmlStrlen(ent->name);
		    const xmlChar *cur = ent->name;

		    /*
		     * This may look absurd but is needed to detect
		     * entities problems
		     */
		    if ((ent->etype != XML_INTERNAL_PREDEFINED_ENTITY) &&
			(ent->content != NULL) && (ent->checked == 0)) {
			unsigned long oldnbent = ctxt->nbentities;

			++ctxt->depth;
			rep = xmlStringDecodeEntities(ctxt, ent->content,
						  XML_SUBSTITUTE_REF, 0, 0, 0);
			--ctxt->depth;

			ent->checked = (ctxt->nbentities - oldnbent + 1) * 2;
			if (rep != NULL) {
			    if (xmlStrchr(rep, '<'))
			        ent->checked |= 1;
			    xmlFree(rep);
			    rep = NULL;
			} else {
                            ent->content[0] = 0;
                        }
		    }

		    /*
		     * Just output the reference
		     */
		    buf[len++] = '&';
		    while (len + i + 10 > buf_size) {
			growBuffer(buf, i + 10);
		    }
		    for (;i > 0;i--)
			buf[len++] = *cur++;
		    buf[len++] = ';';
		}
	    }
	} else {
	    if ((c == 0x20) || (c == 0xD) || (c == 0xA) || (c == 0x9)) {
	        if ((len != 0) || (!normalize)) {
		    if ((!normalize) || (!in_space)) {
			COPY_BUF(l,buf,len,0x20);
			while (len + 10 > buf_size) {
			    growBuffer(buf, 10);
			}
		    }
		    in_space = 1;
		}
	    } else {
	        in_space = 0;
		COPY_BUF(l,buf,len,c);
		if (len + 10 > buf_size) {
		    growBuffer(buf, 10);
		}
	    }
	    NEXTL(l);
	}
	GROW;
	c = CUR_CHAR(l);
    }
    if (ctxt->instate == XML_PARSER_EOF)
        goto error;

    if ((in_space) && (normalize)) {
        while ((len > 0) && (buf[len - 1] == 0x20)) len--;
    }
    buf[len] = 0;
    if (RAW == '<') {
	xmlFatalErr(ctxt, XML_ERR_LT_IN_ATTRIBUTE, NULL);
    } else if (RAW != limit) {
	if ((c != 0) && (!IS_CHAR(c))) {
	    xmlFatalErrMsg(ctxt, XML_ERR_INVALID_CHAR,
			   "invalid character in attribute value\n");
	} else {
	    xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
			   "AttValue: ' expected\n");
        }
    } else
	NEXT;

    /*
     * There we potentially risk an overflow, don't allow attribute value of
     * length more than INT_MAX it is a very reasonnable assumption !
     */
    if (len >= INT_MAX) {
        xmlFatalErrMsg(ctxt, XML_ERR_ATTRIBUTE_NOT_FINISHED,
                       "AttValue length too long\n");
        goto mem_error;
    }

    if (attlen != NULL) *attlen = (int) len;
    return(buf);

mem_error:
    xmlErrMemory(ctxt, NULL);
error:
    if (buf != NULL)
        xmlFree(buf);
    if (rep != NULL)
        xmlFree(rep);
    return(NULL);
}