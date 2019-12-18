#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlCharEncodingHandlerPtr ;
typedef  int /*<<< orphan*/  xmlCharEncodingHandler ;
typedef  scalar_t__ xmlCharEncoding ;
typedef  int /*<<< orphan*/  uconv_t ;
typedef  scalar_t__ iconv_t ;
struct TYPE_6__ {char const* name; int /*<<< orphan*/ * uconv_out; int /*<<< orphan*/ * uconv_in; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; scalar_t__ iconv_out; scalar_t__ iconv_in; } ;

/* Variables and functions */
 scalar_t__ XML_CHAR_ENCODING_ERROR ; 
 int /*<<< orphan*/  XML_ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  closeIcuConverter (int /*<<< orphan*/ *) ; 
 TYPE_1__** handlers ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int nbCharEncodingHandler ; 
 int /*<<< orphan*/ * openIcuConverter (char const*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 char toupper (char const) ; 
 TYPE_1__* xmlDefaultCharEncodingHandler ; 
 int /*<<< orphan*/  xmlEncodingErr (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 
 char* xmlGetCharEncodingName (scalar_t__) ; 
 char* xmlGetEncodingAlias (char const*) ; 
 int /*<<< orphan*/  xmlInitCharEncodingHandlers () ; 
 scalar_t__ xmlMalloc (int) ; 
 void* xmlMemStrdup (char const*) ; 
 scalar_t__ xmlParseCharEncoding (char const*) ; 

xmlCharEncodingHandlerPtr
xmlFindCharEncodingHandler(const char *name) {
    const char *nalias;
    const char *norig;
    xmlCharEncoding alias;
#ifdef LIBXML_ICONV_ENABLED
    xmlCharEncodingHandlerPtr enc;
    iconv_t icv_in, icv_out;
#endif /* LIBXML_ICONV_ENABLED */
#ifdef LIBXML_ICU_ENABLED
    xmlCharEncodingHandlerPtr encu;
    uconv_t *ucv_in, *ucv_out;
#endif /* LIBXML_ICU_ENABLED */
    char upper[100];
    int i;

    if (handlers == NULL) xmlInitCharEncodingHandlers();
    if (name == NULL) return(xmlDefaultCharEncodingHandler);
    if (name[0] == 0) return(xmlDefaultCharEncodingHandler);

    /*
     * Do the alias resolution
     */
    norig = name;
    nalias = xmlGetEncodingAlias(name);
    if (nalias != NULL)
	name = nalias;

    /*
     * Check first for directly registered encoding names
     */
    for (i = 0;i < 99;i++) {
        upper[i] = toupper(name[i]);
	if (upper[i] == 0) break;
    }
    upper[i] = 0;

    if (handlers != NULL) {
        for (i = 0;i < nbCharEncodingHandler; i++) {
            if (!strcmp(upper, handlers[i]->name)) {
#ifdef DEBUG_ENCODING
                xmlGenericError(xmlGenericErrorContext,
                        "Found registered handler for encoding %s\n", name);
#endif
                return(handlers[i]);
            }
        }
    }

#ifdef LIBXML_ICONV_ENABLED
    /* check whether iconv can handle this */
    icv_in = iconv_open("UTF-8", name);
    icv_out = iconv_open(name, "UTF-8");
    if (icv_in == (iconv_t) -1) {
        icv_in = iconv_open("UTF-8", upper);
    }
    if (icv_out == (iconv_t) -1) {
	icv_out = iconv_open(upper, "UTF-8");
    }
    if ((icv_in != (iconv_t) -1) && (icv_out != (iconv_t) -1)) {
	    enc = (xmlCharEncodingHandlerPtr)
	          xmlMalloc(sizeof(xmlCharEncodingHandler));
	    if (enc == NULL) {
	        iconv_close(icv_in);
	        iconv_close(icv_out);
		return(NULL);
	    }
            memset(enc, 0, sizeof(xmlCharEncodingHandler));
	    enc->name = xmlMemStrdup(name);
	    enc->input = NULL;
	    enc->output = NULL;
	    enc->iconv_in = icv_in;
	    enc->iconv_out = icv_out;
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
		    "Found iconv handler for encoding %s\n", name);
#endif
	    return enc;
    } else if ((icv_in != (iconv_t) -1) || icv_out != (iconv_t) -1) {
	    xmlEncodingErr(XML_ERR_INTERNAL_ERROR,
		    "iconv : problems with filters for '%s'\n", name);
    }
#endif /* LIBXML_ICONV_ENABLED */
#ifdef LIBXML_ICU_ENABLED
    /* check whether icu can handle this */
    ucv_in = openIcuConverter(name, 1);
    ucv_out = openIcuConverter(name, 0);
    if (ucv_in != NULL && ucv_out != NULL) {
	    encu = (xmlCharEncodingHandlerPtr)
	           xmlMalloc(sizeof(xmlCharEncodingHandler));
	    if (encu == NULL) {
                closeIcuConverter(ucv_in);
                closeIcuConverter(ucv_out);
		return(NULL);
	    }
            memset(encu, 0, sizeof(xmlCharEncodingHandler));
	    encu->name = xmlMemStrdup(name);
	    encu->input = NULL;
	    encu->output = NULL;
	    encu->uconv_in = ucv_in;
	    encu->uconv_out = ucv_out;
#ifdef DEBUG_ENCODING
            xmlGenericError(xmlGenericErrorContext,
		    "Found ICU converter handler for encoding %s\n", name);
#endif
	    return encu;
    } else if (ucv_in != NULL || ucv_out != NULL) {
            closeIcuConverter(ucv_in);
            closeIcuConverter(ucv_out);
	    xmlEncodingErr(XML_ERR_INTERNAL_ERROR,
		    "ICU converter : problems with filters for '%s'\n", name);
    }
#endif /* LIBXML_ICU_ENABLED */

#ifdef DEBUG_ENCODING
    xmlGenericError(xmlGenericErrorContext,
	    "No handler found for encoding %s\n", name);
#endif

    /*
     * Fallback using the canonical names
     */
    alias = xmlParseCharEncoding(norig);
    if (alias != XML_CHAR_ENCODING_ERROR) {
        const char* canon;
        canon = xmlGetCharEncodingName(alias);
        if ((canon != NULL) && (strcmp(name, canon))) {
	    return(xmlFindCharEncodingHandler(canon));
        }
    }

    /* If "none of the above", give up */
    return(NULL);
}