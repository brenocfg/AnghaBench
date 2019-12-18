__attribute__((used)) static const char *httpd_ReasonFromCode(unsigned i_code)
{
    typedef struct
    {
        unsigned   i_code;
        const char psz_reason[36];
    } http_status_info;

    static const http_status_info http_reason[] =
    {
        /*{ 100, "Continue" },
          { 101, "Switching Protocols" },*/
        { 200, "OK" },
        /*{ 201, "Created" },
          { 202, "Accepted" },
          { 203, "Non-authoritative information" },
          { 204, "No content" },
          { 205, "Reset content" },
          { 206, "Partial content" },
          { 250, "Low on storage space" },
          { 300, "Multiple choices" },*/
        { 301, "Moved permanently" },
        /*{ 302, "Moved temporarily" },
          { 303, "See other" },
          { 304, "Not modified" },
          { 305, "Use proxy" },
          { 307, "Temporary redirect" },
          { 400, "Bad request" },*/
        { 401, "Unauthorized" },
        /*{ 402, "Payment Required" },*/
        { 403, "Forbidden" },
        { 404, "Not found" },
        { 405, "Method not allowed" },
        /*{ 406, "Not acceptable" },
          { 407, "Proxy authentication required" },
          { 408, "Request time-out" },
          { 409, "Conflict" },
          { 410, "Gone" },
          { 411, "Length required" },
          { 412, "Precondition failed" },
          { 413, "Request entity too large" },
          { 414, "Request-URI too large" },
          { 415, "Unsupported media Type" },
          { 416, "Requested range not satisfiable" },
          { 417, "Expectation failed" },
          { 451, "Parameter not understood" },
          { 452, "Conference not found" },
          { 453, "Not enough bandwidth" },*/
        { 454, "Session not found" },
        { 455, "Method not valid in this State" },
        { 456, "Header field not valid for resource" },
        { 457, "Invalid range" },
        /*{ 458, "Read-only parameter" },*/
        { 459, "Aggregate operation not allowed" },
        { 460, "Non-aggregate operation not allowed" },
        { 461, "Unsupported transport" },
        /*{ 462, "Destination unreachable" },*/
        { 500, "Internal server error" },
        { 501, "Not implemented" },
        /*{ 502, "Bad gateway" },*/
        { 503, "Service unavailable" },
        /*{ 504, "Gateway time-out" },*/
        { 505, "Protocol version not supported" },
        { 551, "Option not supported" },
        { 999, "" }
    };

    static const char psz_fallback_reason[5][16] = {
        "Continue", "OK", "Found", "Client error", "Server error"
    };

    assert((i_code >= 100) && (i_code <= 599));

    const http_status_info *p = http_reason;
    while (i_code < p->i_code)
        p++;

    if (p->i_code == i_code)
        return p->psz_reason;

    return psz_fallback_reason[(i_code / 100) - 1];
}