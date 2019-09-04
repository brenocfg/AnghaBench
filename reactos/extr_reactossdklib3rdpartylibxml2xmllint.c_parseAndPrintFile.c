#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* xmlParserCtxtPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/ * xmlDtdPtr ;
typedef  int /*<<< orphan*/ * xmlDocPtr ;
struct TYPE_10__ {int /*<<< orphan*/  warning; int /*<<< orphan*/  error; } ;
struct TYPE_11__ {TYPE_2__ vctxt; TYPE_1__* sax; } ;
struct TYPE_9__ {int /*<<< orphan*/  warning; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  XMLLINT_ERR_UNCLASS ; 
 scalar_t__ dropdtd ; 
 int /*<<< orphan*/  endTimer (char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ htmlout ; 
 int /*<<< orphan*/  myClose ; 
 int /*<<< orphan*/  myRead ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  progresult ; 
 int /*<<< orphan*/  repeat ; 
 int /*<<< orphan*/  startTimer () ; 
 scalar_t__ testIO ; 
 scalar_t__ timing ; 
 int /*<<< orphan*/ * xmlCtxtReadFile (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlCtxtReadIO (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlFreeDoc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeDtd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeParserCtxt (TYPE_3__*) ; 
 int /*<<< orphan*/ * xmlGetIntSubset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlHTMLError ; 
 int /*<<< orphan*/  xmlHTMLValidityError ; 
 int /*<<< orphan*/  xmlHTMLValidityWarning ; 
 int /*<<< orphan*/  xmlHTMLWarning ; 
 TYPE_3__* xmlNewParserCtxt () ; 
 int /*<<< orphan*/ * xmlReadFd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlReadFile (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmlReadIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlUnlinkNode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parseAndPrintFile(char *filename, xmlParserCtxtPtr rectxt) {
    xmlDocPtr doc = NULL;
#ifdef LIBXML_TREE_ENABLED
    xmlDocPtr tmp;
#endif /* LIBXML_TREE_ENABLED */

    if ((timing) && (!repeat))
	startTimer();


#ifdef LIBXML_TREE_ENABLED
    if (filename == NULL) {
	if (generate) {
	    xmlNodePtr n;

	    doc = xmlNewDoc(BAD_CAST "1.0");
	    n = xmlNewDocNode(doc, NULL, BAD_CAST "info", NULL);
	    xmlNodeSetContent(n, BAD_CAST "abc");
	    xmlDocSetRootElement(doc, n);
	}
    }
#endif /* LIBXML_TREE_ENABLED */
#ifdef LIBXML_HTML_ENABLED
#ifdef LIBXML_PUSH_ENABLED
    else if ((html) && (push)) {
        FILE *f;

#if defined(_WIN32) || defined (__DJGPP__) && !defined (__CYGWIN__)
	f = fopen(filename, "rb");
#elif defined(__OS400__)
	f = fopen(filename, "rb");
#else
	f = fopen(filename, "r");
#endif
        if (f != NULL) {
            int res;
            char chars[4096];
            htmlParserCtxtPtr ctxt;

            res = fread(chars, 1, 4, f);
            if (res > 0) {
                ctxt = htmlCreatePushParserCtxt(NULL, NULL,
                            chars, res, filename, XML_CHAR_ENCODING_NONE);
                xmlCtxtUseOptions(ctxt, options);
                while ((res = fread(chars, 1, pushsize, f)) > 0) {
                    htmlParseChunk(ctxt, chars, res, 0);
                }
                htmlParseChunk(ctxt, chars, 0, 1);
                doc = ctxt->myDoc;
                htmlFreeParserCtxt(ctxt);
            }
            fclose(f);
        }
    }
#endif /* LIBXML_PUSH_ENABLED */
#ifdef HAVE_MMAP
    else if ((html) && (memory)) {
	int fd;
	struct stat info;
	const char *base;
	if (stat(filename, &info) < 0)
	    return;
	if ((fd = open(filename, O_RDONLY)) < 0)
	    return;
	base = mmap(NULL, info.st_size, PROT_READ, MAP_SHARED, fd, 0) ;
	if (base == (void *) MAP_FAILED) {
	    close(fd);
	    fprintf(stderr, "mmap failure for file %s\n", filename);
	    progresult = XMLLINT_ERR_RDFILE;
	    return;
	}

	doc = htmlReadMemory((char *) base, info.st_size, filename,
	                     NULL, options);

	munmap((char *) base, info.st_size);
	close(fd);
    }
#endif
    else if (html) {
	doc = htmlReadFile(filename, NULL, options);
    }
#endif /* LIBXML_HTML_ENABLED */
    else {
#ifdef LIBXML_PUSH_ENABLED
	/*
	 * build an XML tree from a string;
	 */
	if (push) {
	    FILE *f;

	    /* '-' Usually means stdin -<sven@zen.org> */
	    if ((filename[0] == '-') && (filename[1] == 0)) {
	      f = stdin;
	    } else {
#if defined(_WIN32) || defined (__DJGPP__) && !defined (__CYGWIN__)
		f = fopen(filename, "rb");
#elif defined(__OS400__)
		f = fopen(filename, "rb");
#else
		f = fopen(filename, "r");
#endif
	    }
	    if (f != NULL) {
		int ret;
	        int res, size = 1024;
	        char chars[1024];
                xmlParserCtxtPtr ctxt;

		/* if (repeat) size = 1024; */
		res = fread(chars, 1, 4, f);
		if (res > 0) {
		    ctxt = xmlCreatePushParserCtxt(NULL, NULL,
		                chars, res, filename);
		    xmlCtxtUseOptions(ctxt, options);
		    while ((res = fread(chars, 1, size, f)) > 0) {
			xmlParseChunk(ctxt, chars, res, 0);
		    }
		    xmlParseChunk(ctxt, chars, 0, 1);
		    doc = ctxt->myDoc;
		    ret = ctxt->wellFormed;
		    xmlFreeParserCtxt(ctxt);
		    if (!ret) {
			xmlFreeDoc(doc);
			doc = NULL;
		    }
	        }
                if (f != stdin)
                    fclose(f);
	    }
	} else
#endif /* LIBXML_PUSH_ENABLED */
        if (testIO) {
	    if ((filename[0] == '-') && (filename[1] == 0)) {
	        doc = xmlReadFd(0, NULL, NULL, options);
	    } else {
	        FILE *f;

#if defined(_WIN32) || defined (__DJGPP__) && !defined (__CYGWIN__)
		f = fopen(filename, "rb");
#elif defined(__OS400__)
		f = fopen(filename, "rb");
#else
		f = fopen(filename, "r");
#endif
		if (f != NULL) {
		    if (rectxt == NULL)
			doc = xmlReadIO(myRead, myClose, f, filename, NULL,
                                        options);
		    else
			doc = xmlCtxtReadIO(rectxt, myRead, myClose, f,
					    filename, NULL, options);
		} else
		    doc = NULL;
	    }
	} else if (htmlout) {
	    xmlParserCtxtPtr ctxt;

	    if (rectxt == NULL)
		ctxt = xmlNewParserCtxt();
	    else
	        ctxt = rectxt;
	    if (ctxt == NULL) {
	        doc = NULL;
	    } else {
	        ctxt->sax->error = xmlHTMLError;
	        ctxt->sax->warning = xmlHTMLWarning;
	        ctxt->vctxt.error = xmlHTMLValidityError;
	        ctxt->vctxt.warning = xmlHTMLValidityWarning;

		doc = xmlCtxtReadFile(ctxt, filename, NULL, options);

		if (rectxt == NULL)
		    xmlFreeParserCtxt(ctxt);
	    }
#ifdef HAVE_MMAP
	} else if (memory) {
	    int fd;
	    struct stat info;
	    const char *base;
	    if (stat(filename, &info) < 0)
		return;
	    if ((fd = open(filename, O_RDONLY)) < 0)
		return;
	    base = mmap(NULL, info.st_size, PROT_READ, MAP_SHARED, fd, 0) ;
	    if (base == (void *) MAP_FAILED) {
	        close(fd);
	        fprintf(stderr, "mmap failure for file %s\n", filename);
		progresult = XMLLINT_ERR_RDFILE;
	        return;
	    }

	    if (rectxt == NULL)
		doc = xmlReadMemory((char *) base, info.st_size,
		                    filename, NULL, options);
	    else
		doc = xmlCtxtReadMemory(rectxt, (char *) base, info.st_size,
			                filename, NULL, options);

	    munmap((char *) base, info.st_size);
	    close(fd);
#endif
#ifdef LIBXML_VALID_ENABLED
	} else if (valid) {
	    xmlParserCtxtPtr ctxt = NULL;

	    if (rectxt == NULL)
		ctxt = xmlNewParserCtxt();
	    else
	        ctxt = rectxt;
	    if (ctxt == NULL) {
	        doc = NULL;
	    } else {
		doc = xmlCtxtReadFile(ctxt, filename, NULL, options);

		if (ctxt->valid == 0)
		    progresult = XMLLINT_ERR_RDFILE;
		if (rectxt == NULL)
		    xmlFreeParserCtxt(ctxt);
	    }
#endif /* LIBXML_VALID_ENABLED */
	} else {
	    if (rectxt != NULL)
	        doc = xmlCtxtReadFile(rectxt, filename, NULL, options);
	    else {
#ifdef LIBXML_SAX1_ENABLED
                if (sax1)
		    doc = xmlParseFile(filename);
		else
#endif /* LIBXML_SAX1_ENABLED */
		doc = xmlReadFile(filename, NULL, options);
	    }
	}
    }

    /*
     * If we don't have a document we might as well give up.  Do we
     * want an error message here?  <sven@zen.org> */
    if (doc == NULL) {
	progresult = XMLLINT_ERR_UNCLASS;
	return;
    }

    if ((timing) && (!repeat)) {
	endTimer("Parsing");
    }

    /*
     * Remove DOCTYPE nodes
     */
    if (dropdtd) {
	xmlDtdPtr dtd;

	dtd = xmlGetIntSubset(doc);
	if (dtd != NULL) {
	    xmlUnlinkNode((xmlNodePtr)dtd);
	    xmlFreeDtd(dtd);
	}
    }

#ifdef LIBXML_XINCLUDE_ENABLED
    if (xinclude) {
	if ((timing) && (!repeat)) {
	    startTimer();
	}
	if (xmlXIncludeProcessFlags(doc, options) < 0)
	    progresult = XMLLINT_ERR_UNCLASS;
	if ((timing) && (!repeat)) {
	    endTimer("Xinclude processing");
	}
    }
#endif

#ifdef LIBXML_XPATH_ENABLED
    if (xpathquery != NULL) {
        doXPathQuery(doc, xpathquery);
    }
#endif

#ifdef LIBXML_DEBUG_ENABLED
#ifdef LIBXML_XPATH_ENABLED
    /*
     * shell interaction
     */
    if (shell) {
        xmlXPathOrderDocElems(doc);
        xmlShell(doc, filename, xmlShellReadline, stdout);
    }
#endif
#endif

#ifdef LIBXML_TREE_ENABLED
    /*
     * test intermediate copy if needed.
     */
    if (copy) {
        tmp = doc;
	if (timing) {
	    startTimer();
	}
	doc = xmlCopyDoc(doc, 1);
	if (timing) {
	    endTimer("Copying");
	}
	if (timing) {
	    startTimer();
	}
	xmlFreeDoc(tmp);
	if (timing) {
	    endTimer("Freeing original");
	}
    }
#endif /* LIBXML_TREE_ENABLED */

#ifdef LIBXML_VALID_ENABLED
    if ((insert) && (!html)) {
        const xmlChar* list[256];
	int nb, i;
	xmlNodePtr node;

	if (doc->children != NULL) {
	    node = doc->children;
	    while ((node != NULL) && (node->last == NULL)) node = node->next;
	    if (node != NULL) {
		nb = xmlValidGetValidElements(node->last, NULL, list, 256);
		if (nb < 0) {
		    fprintf(stderr, "could not get valid list of elements\n");
		} else if (nb == 0) {
		    fprintf(stderr, "No element can be inserted under root\n");
		} else {
		    fprintf(stderr, "%d element types can be inserted under root:\n",
		           nb);
		    for (i = 0;i < nb;i++) {
			 fprintf(stderr, "%s\n", (char *) list[i]);
		    }
		}
	    }
	}
    }else
#endif /* LIBXML_VALID_ENABLED */
#ifdef LIBXML_READER_ENABLED
    if (walker) {
        walkDoc(doc);
    }
#endif /* LIBXML_READER_ENABLED */
#ifdef LIBXML_OUTPUT_ENABLED
    if (noout == 0) {
        int ret;

	/*
	 * print it.
	 */
#ifdef LIBXML_DEBUG_ENABLED
	if (!debug) {
#endif
	    if ((timing) && (!repeat)) {
		startTimer();
	    }
#ifdef LIBXML_HTML_ENABLED
            if ((html) && (!xmlout)) {
		if (compress) {
		    htmlSaveFile(output ? output : "-", doc);
		}
		else if (encoding != NULL) {
		    if (format == 1) {
			htmlSaveFileFormat(output ? output : "-", doc, encoding, 1);
		    }
		    else {
			htmlSaveFileFormat(output ? output : "-", doc, encoding, 0);
		    }
		}
		else if (format == 1) {
		    htmlSaveFileFormat(output ? output : "-", doc, NULL, 1);
		}
		else {
		    FILE *out;
		    if (output == NULL)
			out = stdout;
		    else {
			out = fopen(output,"wb");
		    }
		    if (out != NULL) {
			if (htmlDocDump(out, doc) < 0)
			    progresult = XMLLINT_ERR_OUT;

			if (output != NULL)
			    fclose(out);
		    } else {
			fprintf(stderr, "failed to open %s\n", output);
			progresult = XMLLINT_ERR_OUT;
		    }
		}
		if ((timing) && (!repeat)) {
		    endTimer("Saving");
		}
	    } else
#endif
#ifdef LIBXML_C14N_ENABLED
            if (canonical) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_1_0, NULL, 1, &result);
		if (size >= 0) {
		    if (write(1, result, size) == -1) {
		        fprintf(stderr, "Can't write data\n");
		    }
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else if (canonical_11) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_1_1, NULL, 1, &result);
		if (size >= 0) {
		    if (write(1, result, size) == -1) {
		        fprintf(stderr, "Can't write data\n");
		    }
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else
            if (exc_canonical) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_EXCLUSIVE_1_0, NULL, 1, &result);
		if (size >= 0) {
		    if (write(1, result, size) == -1) {
		        fprintf(stderr, "Can't write data\n");
		    }
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else
#endif
#ifdef HAVE_MMAP
	    if (memory) {
		xmlChar *result;
		int len;

		if (encoding != NULL) {
		    if (format == 1) {
		        xmlDocDumpFormatMemoryEnc(doc, &result, &len, encoding, 1);
		    } else {
			xmlDocDumpMemoryEnc(doc, &result, &len, encoding);
		    }
		} else {
		    if (format == 1)
			xmlDocDumpFormatMemory(doc, &result, &len, 1);
		    else
			xmlDocDumpMemory(doc, &result, &len);
		}
		if (result == NULL) {
		    fprintf(stderr, "Failed to save\n");
		    progresult = XMLLINT_ERR_OUT;
		} else {
		    if (write(1, result, len) == -1) {
		        fprintf(stderr, "Can't write data\n");
		    }
		    xmlFree(result);
		}

	    } else
#endif /* HAVE_MMAP */
	    if (compress) {
		xmlSaveFile(output ? output : "-", doc);
	    } else if (oldout) {
	        if (encoding != NULL) {
		    if (format == 1) {
			ret = xmlSaveFormatFileEnc(output ? output : "-", doc,
						   encoding, 1);
		    }
		    else {
			ret = xmlSaveFileEnc(output ? output : "-", doc,
			                     encoding);
		    }
		    if (ret < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		} else if (format == 1) {
		    ret = xmlSaveFormatFile(output ? output : "-", doc, 1);
		    if (ret < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		} else {
		    FILE *out;
		    if (output == NULL)
			out = stdout;
		    else {
			out = fopen(output,"wb");
		    }
		    if (out != NULL) {
			if (xmlDocDump(out, doc) < 0)
			    progresult = XMLLINT_ERR_OUT;

			if (output != NULL)
			    fclose(out);
		    } else {
			fprintf(stderr, "failed to open %s\n", output);
			progresult = XMLLINT_ERR_OUT;
		    }
		}
	    } else {
	        xmlSaveCtxtPtr ctxt;
		int saveOpts = 0;

                if (format == 1)
		    saveOpts |= XML_SAVE_FORMAT;
                else if (format == 2)
                    saveOpts |= XML_SAVE_WSNONSIG;

#if defined(LIBXML_HTML_ENABLED) || defined(LIBXML_VALID_ENABLED)
                if (xmlout)
                    saveOpts |= XML_SAVE_AS_XML;
#endif

		if (output == NULL)
		    ctxt = xmlSaveToFd(1, encoding, saveOpts);
		else
		    ctxt = xmlSaveToFilename(output, encoding, saveOpts);

		if (ctxt != NULL) {
		    if (xmlSaveDoc(ctxt, doc) < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		    xmlSaveClose(ctxt);
		} else {
		    progresult = XMLLINT_ERR_OUT;
		}
	    }
	    if ((timing) && (!repeat)) {
		endTimer("Saving");
	    }
#ifdef LIBXML_DEBUG_ENABLED
	} else {
	    FILE *out;
	    if (output == NULL)
	        out = stdout;
	    else {
		out = fopen(output,"wb");
	    }
	    if (out != NULL) {
		xmlDebugDumpDocument(out, doc);

		if (output != NULL)
		    fclose(out);
	    } else {
		fprintf(stderr, "failed to open %s\n", output);
		progresult = XMLLINT_ERR_OUT;
	    }
	}
#endif
    }
#endif /* LIBXML_OUTPUT_ENABLED */

#ifdef LIBXML_VALID_ENABLED
    /*
     * A posteriori validation test
     */
    if ((dtdvalid != NULL) || (dtdvalidfpi != NULL)) {
	xmlDtdPtr dtd;

	if ((timing) && (!repeat)) {
	    startTimer();
	}
	if (dtdvalid != NULL)
	    dtd = xmlParseDTD(NULL, (const xmlChar *)dtdvalid);
	else
	    dtd = xmlParseDTD((const xmlChar *)dtdvalidfpi, NULL);
	if ((timing) && (!repeat)) {
	    endTimer("Parsing DTD");
	}
	if (dtd == NULL) {
	    if (dtdvalid != NULL)
		xmlGenericError(xmlGenericErrorContext,
			"Could not parse DTD %s\n", dtdvalid);
	    else
		xmlGenericError(xmlGenericErrorContext,
			"Could not parse DTD %s\n", dtdvalidfpi);
	    progresult = XMLLINT_ERR_DTD;
	} else {
	    xmlValidCtxtPtr cvp;

	    if ((cvp = xmlNewValidCtxt()) == NULL) {
		xmlGenericError(xmlGenericErrorContext,
			"Couldn't allocate validation context\n");
		exit(-1);
	    }
	    cvp->userData = (void *) stderr;
	    cvp->error    = (xmlValidityErrorFunc) fprintf;
	    cvp->warning  = (xmlValidityWarningFunc) fprintf;

	    if ((timing) && (!repeat)) {
		startTimer();
	    }
	    if (!xmlValidateDtd(cvp, doc, dtd)) {
		if (dtdvalid != NULL)
		    xmlGenericError(xmlGenericErrorContext,
			    "Document %s does not validate against %s\n",
			    filename, dtdvalid);
		else
		    xmlGenericError(xmlGenericErrorContext,
			    "Document %s does not validate against %s\n",
			    filename, dtdvalidfpi);
		progresult = XMLLINT_ERR_VALID;
	    }
	    if ((timing) && (!repeat)) {
		endTimer("Validating against DTD");
	    }
	    xmlFreeValidCtxt(cvp);
	    xmlFreeDtd(dtd);
	}
    } else if (postvalid) {
	xmlValidCtxtPtr cvp;

	if ((cvp = xmlNewValidCtxt()) == NULL) {
	    xmlGenericError(xmlGenericErrorContext,
		    "Couldn't allocate validation context\n");
	    exit(-1);
	}

	if ((timing) && (!repeat)) {
	    startTimer();
	}
	cvp->userData = (void *) stderr;
	cvp->error    = (xmlValidityErrorFunc) fprintf;
	cvp->warning  = (xmlValidityWarningFunc) fprintf;
	if (!xmlValidateDocument(cvp, doc)) {
	    xmlGenericError(xmlGenericErrorContext,
		    "Document %s does not validate\n", filename);
	    progresult = XMLLINT_ERR_VALID;
	}
	if ((timing) && (!repeat)) {
	    endTimer("Validating");
	}
	xmlFreeValidCtxt(cvp);
    }
#endif /* LIBXML_VALID_ENABLED */
#ifdef LIBXML_SCHEMATRON_ENABLED
    if (wxschematron != NULL) {
	xmlSchematronValidCtxtPtr ctxt;
	int ret;
	int flag;

	if ((timing) && (!repeat)) {
	    startTimer();
	}

	if (debug)
	    flag = XML_SCHEMATRON_OUT_XML;
	else
	    flag = XML_SCHEMATRON_OUT_TEXT;
	if (noout)
	    flag |= XML_SCHEMATRON_OUT_QUIET;
	ctxt = xmlSchematronNewValidCtxt(wxschematron, flag);
#if 0
	xmlSchematronSetValidErrors(ctxt,
		(xmlSchematronValidityErrorFunc) fprintf,
		(xmlSchematronValidityWarningFunc) fprintf,
		stderr);
#endif
	ret = xmlSchematronValidateDoc(ctxt, doc);
	if (ret == 0) {
	    fprintf(stderr, "%s validates\n", filename);
	} else if (ret > 0) {
	    fprintf(stderr, "%s fails to validate\n", filename);
	    progresult = XMLLINT_ERR_VALID;
	} else {
	    fprintf(stderr, "%s validation generated an internal error\n",
		   filename);
	    progresult = XMLLINT_ERR_VALID;
	}
	xmlSchematronFreeValidCtxt(ctxt);
	if ((timing) && (!repeat)) {
	    endTimer("Validating");
	}
    }
#endif
#ifdef LIBXML_SCHEMAS_ENABLED
    if (relaxngschemas != NULL) {
	xmlRelaxNGValidCtxtPtr ctxt;
	int ret;

	if ((timing) && (!repeat)) {
	    startTimer();
	}

	ctxt = xmlRelaxNGNewValidCtxt(relaxngschemas);
	xmlRelaxNGSetValidErrors(ctxt,
		(xmlRelaxNGValidityErrorFunc) fprintf,
		(xmlRelaxNGValidityWarningFunc) fprintf,
		stderr);
	ret = xmlRelaxNGValidateDoc(ctxt, doc);
	if (ret == 0) {
	    fprintf(stderr, "%s validates\n", filename);
	} else if (ret > 0) {
	    fprintf(stderr, "%s fails to validate\n", filename);
	    progresult = XMLLINT_ERR_VALID;
	} else {
	    fprintf(stderr, "%s validation generated an internal error\n",
		   filename);
	    progresult = XMLLINT_ERR_VALID;
	}
	xmlRelaxNGFreeValidCtxt(ctxt);
	if ((timing) && (!repeat)) {
	    endTimer("Validating");
	}
    } else if (wxschemas != NULL) {
	xmlSchemaValidCtxtPtr ctxt;
	int ret;

	if ((timing) && (!repeat)) {
	    startTimer();
	}

	ctxt = xmlSchemaNewValidCtxt(wxschemas);
	xmlSchemaSetValidErrors(ctxt,
		(xmlSchemaValidityErrorFunc) fprintf,
		(xmlSchemaValidityWarningFunc) fprintf,
		stderr);
	ret = xmlSchemaValidateDoc(ctxt, doc);
	if (ret == 0) {
	    fprintf(stderr, "%s validates\n", filename);
	} else if (ret > 0) {
	    fprintf(stderr, "%s fails to validate\n", filename);
	    progresult = XMLLINT_ERR_VALID;
	} else {
	    fprintf(stderr, "%s validation generated an internal error\n",
		   filename);
	    progresult = XMLLINT_ERR_VALID;
	}
	xmlSchemaFreeValidCtxt(ctxt);
	if ((timing) && (!repeat)) {
	    endTimer("Validating");
	}
    }
#endif

#ifdef LIBXML_DEBUG_ENABLED
#if defined(LIBXML_HTML_ENABLED) || defined(LIBXML_VALID_ENABLED)
    if ((debugent) && (!html))
	xmlDebugDumpEntities(stderr, doc);
#endif
#endif

    /*
     * free it.
     */
    if ((timing) && (!repeat)) {
	startTimer();
    }
    xmlFreeDoc(doc);
    if ((timing) && (!repeat)) {
	endTimer("Freeing");
    }
}