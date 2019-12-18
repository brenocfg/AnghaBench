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
typedef  int /*<<< orphan*/  error_string ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BOOL ; 
#define  ERROR_FTP_DROPPED 203 
#define  ERROR_FTP_TRANSFER_IN_PROGRESS 202 
#define  ERROR_GOPHER_ATTRIBUTE_NOT_FOUND 201 
#define  ERROR_GOPHER_DATA_ERROR 200 
#define  ERROR_GOPHER_END_OF_DATA 199 
#define  ERROR_GOPHER_INCORRECT_LOCATOR_TYPE 198 
#define  ERROR_GOPHER_INVALID_LOCATOR 197 
#define  ERROR_GOPHER_NOT_FILE 196 
#define  ERROR_GOPHER_NOT_GOPHER_PLUS 195 
#define  ERROR_GOPHER_PROTOCOL_ERROR 194 
#define  ERROR_GOPHER_UNKNOWN_LOCATOR 193 
#define  ERROR_HTTP_DOWNLEVEL_SERVER 192 
#define  ERROR_HTTP_HEADER_ALREADY_EXISTS 191 
#define  ERROR_HTTP_HEADER_NOT_FOUND 190 
#define  ERROR_HTTP_INVALID_HEADER 189 
#define  ERROR_HTTP_INVALID_QUERY_REQUEST 188 
#define  ERROR_HTTP_INVALID_SERVER_RESPONSE 187 
#define  ERROR_HTTP_REDIRECT_FAILED 186 
#define  ERROR_INTERNET_BAD_AUTO_PROXY_SCRIPT 185 
#define  ERROR_INTERNET_BAD_OPTION_LENGTH 184 
#define  ERROR_INTERNET_BAD_REGISTRY_PARAMETER 183 
#define  ERROR_INTERNET_CANNOT_CONNECT 182 
#define  ERROR_INTERNET_CHG_POST_IS_NON_SECURE 181 
#define  ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED 180 
#define  ERROR_INTERNET_CONNECTION_ABORTED 179 
#define  ERROR_INTERNET_CONNECTION_RESET 178 
#define  ERROR_INTERNET_DISCONNECTED 177 
#define  ERROR_INTERNET_EXTENDED_ERROR 176 
#define  ERROR_INTERNET_FAILED_DUETOSECURITYCHECK 175 
#define  ERROR_INTERNET_FORCE_RETRY 174 
#define  ERROR_INTERNET_HANDLE_EXISTS 173 
#define  ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR 172 
#define  ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR 171 
#define  ERROR_INTERNET_INCORRECT_FORMAT 170 
#define  ERROR_INTERNET_INCORRECT_HANDLE_STATE 169 
#define  ERROR_INTERNET_INCORRECT_HANDLE_TYPE 168 
#define  ERROR_INTERNET_INCORRECT_PASSWORD 167 
#define  ERROR_INTERNET_INCORRECT_USER_NAME 166 
#define  ERROR_INTERNET_INTERNAL_ERROR 165 
#define  ERROR_INTERNET_INVALID_OPERATION 164 
#define  ERROR_INTERNET_INVALID_OPTION 163 
#define  ERROR_INTERNET_INVALID_PROXY_REQUEST 162 
#define  ERROR_INTERNET_INVALID_URL 161 
#define  ERROR_INTERNET_ITEM_NOT_FOUND 160 
#define  ERROR_INTERNET_LOGIN_FAILURE 159 
#define  ERROR_INTERNET_LOGIN_FAILURE_DISPLAY_ENTITY_BODY 158 
#define  ERROR_INTERNET_MIXED_SECURITY 157 
#define  ERROR_INTERNET_NAME_NOT_RESOLVED 156 
#define  ERROR_INTERNET_NEED_MSN_SSPI_PKG 155 
#define  ERROR_INTERNET_NOT_INITIALIZED 154 
#define  ERROR_INTERNET_NOT_PROXY_REQUEST 153 
#define  ERROR_INTERNET_NO_CALLBACK 152 
#define  ERROR_INTERNET_NO_CONTEXT 151 
#define  ERROR_INTERNET_NO_DIRECT_ACCESS 150 
#define  ERROR_INTERNET_OPERATION_CANCELLED 149 
#define  ERROR_INTERNET_OPTION_NOT_SETTABLE 148 
#define  ERROR_INTERNET_OUT_OF_HANDLES 147 
#define  ERROR_INTERNET_POST_IS_NON_SECURE 146 
#define  ERROR_INTERNET_PROTOCOL_NOT_FOUND 145 
#define  ERROR_INTERNET_PROXY_SERVER_UNREACHABLE 144 
#define  ERROR_INTERNET_REGISTRY_VALUE_NOT_FOUND 143 
#define  ERROR_INTERNET_REQUEST_PENDING 142 
#define  ERROR_INTERNET_SECURITY_CHANNEL_ERROR 141 
#define  ERROR_INTERNET_SEC_CERT_CN_INVALID 140 
#define  ERROR_INTERNET_SEC_CERT_DATE_INVALID 139 
#define  ERROR_INTERNET_SEC_CERT_ERRORS 138 
#define  ERROR_INTERNET_SEC_CERT_NO_REV 137 
#define  ERROR_INTERNET_SEC_CERT_REV_FAILED 136 
#define  ERROR_INTERNET_SEC_INVALID_CERT 135 
#define  ERROR_INTERNET_SERVER_UNREACHABLE 134 
#define  ERROR_INTERNET_SHUTDOWN 133 
#define  ERROR_INTERNET_TCPIP_NOT_INSTALLED 132 
#define  ERROR_INTERNET_TIMEOUT 131 
#define  ERROR_INTERNET_UNABLE_TO_CACHE_FILE 130 
#define  ERROR_INTERNET_UNABLE_TO_DOWNLOAD_SCRIPT 129 
#define  ERROR_INTERNET_UNRECOGNIZED_SCHEME 128 
 int /*<<< orphan*/  GetLastError () ; 
 int HRESULT_CODE (int /*<<< orphan*/ ) ; 
 int INTERNET_ERROR_BASE ; 
 int INTERNET_ERROR_LAST ; 
 int /*<<< orphan*/  InternetGetLastResponseInfoA ; 
 int /*<<< orphan*/  LPDWORD ; 
 int /*<<< orphan*/  LPSTR ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_TYPE_DECL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINAPI ; 
 int /*<<< orphan*/  WinInet ; 
 char const* WindowsErrorString () ; 
 int error_code ; 
 int /*<<< orphan*/  pfInternetGetLastResponseInfoA (int*,char*,int*) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int) ; 

const char* WinInetErrorString(void)
{
	static char error_string[256];
	DWORD size = sizeof(error_string);
	PF_TYPE_DECL(WINAPI, BOOL, InternetGetLastResponseInfoA, (LPDWORD, LPSTR, LPDWORD));
	PF_INIT(InternetGetLastResponseInfoA, WinInet);

	error_code = HRESULT_CODE(GetLastError());

	if ((error_code < INTERNET_ERROR_BASE) || (error_code > INTERNET_ERROR_LAST))
		return WindowsErrorString();

	switch(error_code) {
	case ERROR_INTERNET_OUT_OF_HANDLES:
		return "No more handles could be generated at this time.";
	case ERROR_INTERNET_TIMEOUT:
		return "The request has timed out.";
	case ERROR_INTERNET_INTERNAL_ERROR:
		return "An internal error has occurred.";
	case ERROR_INTERNET_INVALID_URL:
		return "The URL is invalid.";
	case ERROR_INTERNET_UNRECOGNIZED_SCHEME:
		return "The URL scheme could not be recognized or is not supported.";
	case ERROR_INTERNET_NAME_NOT_RESOLVED:
		return "The server name could not be resolved.";
	case ERROR_INTERNET_PROTOCOL_NOT_FOUND:
		return "The requested protocol could not be located.";
	case ERROR_INTERNET_INVALID_OPTION:
		return "A request specified an invalid option value.";
	case ERROR_INTERNET_BAD_OPTION_LENGTH:
		return "The length of an option supplied is incorrect for the type of option specified.";
	case ERROR_INTERNET_OPTION_NOT_SETTABLE:
		return "The request option cannot be set, only queried.";
	case ERROR_INTERNET_SHUTDOWN:
		return "The Win32 Internet function support is being shut down or unloaded.";
	case ERROR_INTERNET_INCORRECT_USER_NAME:
		return "The request to connect and log on to an FTP server could not be completed because the supplied user name is incorrect.";
	case ERROR_INTERNET_INCORRECT_PASSWORD:
		return "The request to connect and log on to an FTP server could not be completed because the supplied password is incorrect.";
	case ERROR_INTERNET_LOGIN_FAILURE:
		return "The request to connect to and log on to an FTP server failed.";
	case ERROR_INTERNET_INVALID_OPERATION:
		return "The requested operation is invalid.";
	case ERROR_INTERNET_OPERATION_CANCELLED:
		return "The operation was cancelled, usually because the handle on which the request was operating was closed before the operation completed.";
	case ERROR_INTERNET_INCORRECT_HANDLE_TYPE:
		return "The type of handle supplied is incorrect for this operation.";
	case ERROR_INTERNET_INCORRECT_HANDLE_STATE:
		return "The requested operation cannot be carried out because the handle supplied is not in the correct state.";
	case ERROR_INTERNET_NOT_PROXY_REQUEST:
		return "The request cannot be made via a proxy.";
	case ERROR_INTERNET_REGISTRY_VALUE_NOT_FOUND:
		return "A required registry value could not be located.";
	case ERROR_INTERNET_BAD_REGISTRY_PARAMETER:
		return "A required registry value was located but is an incorrect type or has an invalid value.";
	case ERROR_INTERNET_NO_DIRECT_ACCESS:
		return "Direct network access cannot be made at this time.";
	case ERROR_INTERNET_NO_CONTEXT:
		return "An asynchronous request could not be made because a zero context value was supplied.";
	case ERROR_INTERNET_NO_CALLBACK:
		return "An asynchronous request could not be made because a callback function has not been set.";
	case ERROR_INTERNET_REQUEST_PENDING:
		return "The required operation could not be completed because one or more requests are pending.";
	case ERROR_INTERNET_INCORRECT_FORMAT:
		return "The format of the request is invalid.";
	case ERROR_INTERNET_ITEM_NOT_FOUND:
		return "The requested item could not be located.";
	case ERROR_INTERNET_CANNOT_CONNECT:
		return "The attempt to connect to the server failed.";
	case ERROR_INTERNET_CONNECTION_ABORTED:
		return "The connection with the server has been terminated.";
	case ERROR_INTERNET_CONNECTION_RESET:
		return "The connection with the server has been reset.";
	case ERROR_INTERNET_FORCE_RETRY:
		return "Calls for the Win32 Internet function to redo the request.";
	case ERROR_INTERNET_INVALID_PROXY_REQUEST:
		return "The request to the proxy was invalid.";
	case ERROR_INTERNET_HANDLE_EXISTS:
		return "The request failed because the handle already exists.";
	case ERROR_INTERNET_SEC_INVALID_CERT:
		return "The SSL certificate is invalid.";
	case ERROR_INTERNET_SEC_CERT_DATE_INVALID:
		return "SSL certificate date that was received from the server is bad. The certificate is expired.";
	case ERROR_INTERNET_SEC_CERT_CN_INVALID:
		return "SSL certificate common name (host name field) is incorrect.";
	case ERROR_INTERNET_SEC_CERT_ERRORS:
		return "The SSL certificate contains errors.";
	case ERROR_INTERNET_SEC_CERT_NO_REV:
		return "The SSL certificate was not revoked.";
	case ERROR_INTERNET_SEC_CERT_REV_FAILED:
		return "The revocation check of the SSL certificate failed.";
	case ERROR_INTERNET_HTTP_TO_HTTPS_ON_REDIR:
		return "The application is moving from a non-SSL to an SSL connection because of a redirect.";
	case ERROR_INTERNET_HTTPS_TO_HTTP_ON_REDIR:
		return "The application is moving from an SSL to an non-SSL connection because of a redirect.";
	case ERROR_INTERNET_MIXED_SECURITY:
		return "Some of the content being viewed may have come from unsecured servers.";
	case ERROR_INTERNET_CHG_POST_IS_NON_SECURE:
		return "The application is posting and attempting to change multiple lines of text on a server that is not secure.";
	case ERROR_INTERNET_POST_IS_NON_SECURE:
		return "The application is posting data to a server that is not secure.";
	case ERROR_FTP_TRANSFER_IN_PROGRESS:
		return "The requested operation cannot be made on the FTP session handle because an operation is already in progress.";
	case ERROR_FTP_DROPPED:
		return "The FTP operation was not completed because the session was aborted.";
	case ERROR_GOPHER_PROTOCOL_ERROR:
	case ERROR_GOPHER_NOT_FILE:
	case ERROR_GOPHER_DATA_ERROR:
	case ERROR_GOPHER_END_OF_DATA:
	case ERROR_GOPHER_INVALID_LOCATOR:
	case ERROR_GOPHER_INCORRECT_LOCATOR_TYPE:
	case ERROR_GOPHER_NOT_GOPHER_PLUS:
	case ERROR_GOPHER_ATTRIBUTE_NOT_FOUND:
	case ERROR_GOPHER_UNKNOWN_LOCATOR:
		return "Gopher? Really??? What is this, 1994?";
	case ERROR_HTTP_HEADER_NOT_FOUND:
		return "The requested header could not be located.";
	case ERROR_HTTP_DOWNLEVEL_SERVER:
		return "The server did not return any headers.";
	case ERROR_HTTP_INVALID_SERVER_RESPONSE:
		return "The server response could not be parsed.";
	case ERROR_HTTP_INVALID_HEADER:
		return "The supplied header is invalid.";
	case ERROR_HTTP_INVALID_QUERY_REQUEST:
		return "The request made to HttpQueryInfo is invalid.";
	case ERROR_HTTP_HEADER_ALREADY_EXISTS:
		return "The header could not be added because it already exists.";
	case ERROR_HTTP_REDIRECT_FAILED:
		return "The redirection failed because either the scheme changed or all attempts made to redirect failed.";
	case ERROR_INTERNET_SECURITY_CHANNEL_ERROR:
		return "This system's SSL library is too old to be able to access this website.";
	case ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED:
		return "Client Authentication certificate needed";
	case ERROR_INTERNET_BAD_AUTO_PROXY_SCRIPT:
		return "Bad auto proxy script.";
	case ERROR_INTERNET_UNABLE_TO_DOWNLOAD_SCRIPT:
		return "Unable to download script.";
	case ERROR_INTERNET_NOT_INITIALIZED:
		return "Internet has not be initialized.";
	case ERROR_INTERNET_UNABLE_TO_CACHE_FILE:
		return "Unable to cache the file.";
	case ERROR_INTERNET_TCPIP_NOT_INSTALLED:
		return "TPC/IP not installed.";
	case ERROR_INTERNET_DISCONNECTED:
		return "Internet is disconnected.";
	case ERROR_INTERNET_SERVER_UNREACHABLE:
		return "Server could not be reached.";
	case ERROR_INTERNET_PROXY_SERVER_UNREACHABLE:
		return "Proxy server could not be reached.";
	case ERROR_INTERNET_FAILED_DUETOSECURITYCHECK:
		return "A security check prevented internet connection.";
	case ERROR_INTERNET_NEED_MSN_SSPI_PKG:
		return "This connection requires an MSN Security Support Provider Interface package.";
	case ERROR_INTERNET_LOGIN_FAILURE_DISPLAY_ENTITY_BODY:
		return "Please ask Microsoft about that one!";
	case ERROR_INTERNET_EXTENDED_ERROR:
		if (pfInternetGetLastResponseInfoA != NULL) {
			pfInternetGetLastResponseInfoA(&error_code, error_string, &size);
			return error_string;
		}
		// fall through
	default:
		static_sprintf(error_string, "Unknown internet error 0x%08lX", error_code);
		return error_string;
	}
}