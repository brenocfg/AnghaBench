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
typedef  int RPC_STATUS ;
typedef  scalar_t__ LONG ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ EPT_NT_CANT_CREATE ; 
 scalar_t__ EPT_NT_CANT_PERFORM_OP ; 
 scalar_t__ EPT_NT_INVALID_ENTRY ; 
 scalar_t__ EPT_NT_NOT_REGISTERED ; 
#define  EPT_S_CANT_CREATE 234 
#define  EPT_S_CANT_PERFORM_OP 233 
#define  EPT_S_INVALID_ENTRY 232 
#define  EPT_S_NOT_REGISTERED 231 
#define  ERROR_ACCESS_DENIED 230 
#define  ERROR_ACCOUNT_DISABLED 229 
#define  ERROR_ACCOUNT_LOCKED_OUT 228 
#define  ERROR_INSUFFICIENT_BUFFER 227 
#define  ERROR_INVALID_HANDLE 226 
#define  ERROR_INVALID_LOGON_HOURS 225 
#define  ERROR_INVALID_PARAMETER 224 
#define  ERROR_INVALID_SECURITY_DESCR 223 
#define  ERROR_MAX_THRDS_REACHED 222 
#define  ERROR_NOACCESS 221 
#define  ERROR_NOT_ENOUGH_SERVER_MEMORY 220 
#define  ERROR_OUTOFMEMORY 219 
#define  ERROR_PASSWORD_EXPIRED 218 
#define  ERROR_PASSWORD_MUST_CHANGE 217 
#define  ERROR_SUCCESS 216 
#define  ERROR_WRONG_PASSWORD 215 
 int FALSE ; 
 scalar_t__ I_RpcMapWin32Status (int) ; 
 scalar_t__ RPC_NT_ADDRESS_ERROR ; 
 scalar_t__ RPC_NT_ALREADY_LISTENING ; 
 scalar_t__ RPC_NT_ALREADY_REGISTERED ; 
 scalar_t__ RPC_NT_BAD_STUB_DATA ; 
 scalar_t__ RPC_NT_BINDING_HAS_NO_AUTH ; 
 scalar_t__ RPC_NT_BYTE_COUNT_TOO_SMALL ; 
 scalar_t__ RPC_NT_CALL_CANCELLED ; 
 scalar_t__ RPC_NT_CALL_FAILED ; 
 scalar_t__ RPC_NT_CALL_FAILED_DNE ; 
 scalar_t__ RPC_NT_CALL_IN_PROGRESS ; 
 scalar_t__ RPC_NT_CANNOT_SUPPORT ; 
 scalar_t__ RPC_NT_CANT_CREATE_ENDPOINT ; 
 scalar_t__ RPC_NT_DUPLICATE_ENDPOINT ; 
 scalar_t__ RPC_NT_ENTRY_ALREADY_EXISTS ; 
 scalar_t__ RPC_NT_ENTRY_NOT_FOUND ; 
 scalar_t__ RPC_NT_ENUM_VALUE_OUT_OF_RANGE ; 
 scalar_t__ RPC_NT_FP_DIV_ZERO ; 
 scalar_t__ RPC_NT_FP_OVERFLOW ; 
 scalar_t__ RPC_NT_FP_UNDERFLOW ; 
 scalar_t__ RPC_NT_GROUP_MEMBER_NOT_FOUND ; 
 scalar_t__ RPC_NT_INCOMPLETE_NAME ; 
 scalar_t__ RPC_NT_INTERFACE_NOT_FOUND ; 
 scalar_t__ RPC_NT_INTERNAL_ERROR ; 
 scalar_t__ RPC_NT_INVALID_ASYNC_CALL ; 
 scalar_t__ RPC_NT_INVALID_ASYNC_HANDLE ; 
 scalar_t__ RPC_NT_INVALID_AUTH_IDENTITY ; 
 scalar_t__ RPC_NT_INVALID_BINDING ; 
 scalar_t__ RPC_NT_INVALID_BOUND ; 
 scalar_t__ RPC_NT_INVALID_ENDPOINT_FORMAT ; 
 scalar_t__ RPC_NT_INVALID_NAF_ID ; 
 scalar_t__ RPC_NT_INVALID_NAME_SYNTAX ; 
 scalar_t__ RPC_NT_INVALID_NETWORK_OPTIONS ; 
 scalar_t__ RPC_NT_INVALID_NET_ADDR ; 
 scalar_t__ RPC_NT_INVALID_OBJECT ; 
 scalar_t__ RPC_NT_INVALID_RPC_PROTSEQ ; 
 scalar_t__ RPC_NT_INVALID_STRING_BINDING ; 
 scalar_t__ RPC_NT_INVALID_STRING_UUID ; 
 scalar_t__ RPC_NT_INVALID_TAG ; 
 scalar_t__ RPC_NT_INVALID_TIMEOUT ; 
 scalar_t__ RPC_NT_INVALID_VERS_OPTION ; 
 scalar_t__ RPC_NT_MAX_CALLS_TOO_SMALL ; 
 scalar_t__ RPC_NT_NAME_SERVICE_UNAVAILABLE ; 
 scalar_t__ RPC_NT_NOTHING_TO_EXPORT ; 
 scalar_t__ RPC_NT_NOT_ALL_OBJS_UNEXPORTED ; 
 scalar_t__ RPC_NT_NOT_LISTENING ; 
 scalar_t__ RPC_NT_NO_BINDINGS ; 
 scalar_t__ RPC_NT_NO_CALL_ACTIVE ; 
 scalar_t__ RPC_NT_NO_CONTEXT_AVAILABLE ; 
 scalar_t__ RPC_NT_NO_ENDPOINT_FOUND ; 
 scalar_t__ RPC_NT_NO_ENTRY_NAME ; 
 scalar_t__ RPC_NT_NO_MORE_BINDINGS ; 
 scalar_t__ RPC_NT_NO_MORE_ENTRIES ; 
 scalar_t__ RPC_NT_NO_MORE_MEMBERS ; 
 scalar_t__ RPC_NT_NO_PROTSEQS ; 
 scalar_t__ RPC_NT_NO_PROTSEQS_REGISTERED ; 
 scalar_t__ RPC_NT_NULL_REF_POINTER ; 
 scalar_t__ RPC_NT_OBJECT_NOT_FOUND ; 
 scalar_t__ RPC_NT_OUT_OF_RESOURCES ; 
 scalar_t__ RPC_NT_PIPE_CLOSED ; 
 scalar_t__ RPC_NT_PIPE_DISCIPLINE_ERROR ; 
 scalar_t__ RPC_NT_PIPE_EMPTY ; 
 scalar_t__ RPC_NT_PROCNUM_OUT_OF_RANGE ; 
 scalar_t__ RPC_NT_PROTOCOL_ERROR ; 
 scalar_t__ RPC_NT_PROTSEQ_NOT_FOUND ; 
 scalar_t__ RPC_NT_PROTSEQ_NOT_SUPPORTED ; 
 scalar_t__ RPC_NT_SERVER_TOO_BUSY ; 
 scalar_t__ RPC_NT_SERVER_UNAVAILABLE ; 
 scalar_t__ RPC_NT_SS_CANNOT_GET_CALL_HANDLE ; 
 scalar_t__ RPC_NT_SS_CHAR_TRANS_OPEN_FAIL ; 
 scalar_t__ RPC_NT_SS_CHAR_TRANS_SHORT_FILE ; 
 scalar_t__ RPC_NT_SS_CONTEXT_DAMAGED ; 
 scalar_t__ RPC_NT_SS_CONTEXT_MISMATCH ; 
 scalar_t__ RPC_NT_SS_HANDLES_MISMATCH ; 
 scalar_t__ RPC_NT_SS_IN_NULL_CONTEXT ; 
 scalar_t__ RPC_NT_STRING_TOO_LONG ; 
 scalar_t__ RPC_NT_TYPE_ALREADY_REGISTERED ; 
 scalar_t__ RPC_NT_UNKNOWN_AUTHN_LEVEL ; 
 scalar_t__ RPC_NT_UNKNOWN_AUTHN_SERVICE ; 
 scalar_t__ RPC_NT_UNKNOWN_AUTHN_TYPE ; 
 scalar_t__ RPC_NT_UNKNOWN_AUTHZ_SERVICE ; 
 scalar_t__ RPC_NT_UNKNOWN_IF ; 
 scalar_t__ RPC_NT_UNKNOWN_MGR_TYPE ; 
 scalar_t__ RPC_NT_UNSUPPORTED_NAME_SYNTAX ; 
 scalar_t__ RPC_NT_UNSUPPORTED_TRANS_SYN ; 
 scalar_t__ RPC_NT_UNSUPPORTED_TYPE ; 
 scalar_t__ RPC_NT_UUID_NO_ADDRESS ; 
 scalar_t__ RPC_NT_WRONG_KIND_OF_BINDING ; 
 scalar_t__ RPC_NT_ZERO_DIVIDE ; 
#define  RPC_S_ADDRESS_ERROR 214 
#define  RPC_S_ALREADY_LISTENING 213 
#define  RPC_S_ALREADY_REGISTERED 212 
#define  RPC_S_BINDING_HAS_NO_AUTH 211 
#define  RPC_S_CALL_CANCELLED 210 
#define  RPC_S_CALL_FAILED 209 
#define  RPC_S_CALL_FAILED_DNE 208 
#define  RPC_S_CALL_IN_PROGRESS 207 
#define  RPC_S_CANNOT_SUPPORT 206 
#define  RPC_S_CANT_CREATE_ENDPOINT 205 
#define  RPC_S_DUPLICATE_ENDPOINT 204 
#define  RPC_S_ENTRY_ALREADY_EXISTS 203 
#define  RPC_S_ENTRY_NOT_FOUND 202 
#define  RPC_S_FP_DIV_ZERO 201 
#define  RPC_S_FP_OVERFLOW 200 
#define  RPC_S_FP_UNDERFLOW 199 
#define  RPC_S_GROUP_MEMBER_NOT_FOUND 198 
#define  RPC_S_INCOMPLETE_NAME 197 
#define  RPC_S_INTERFACE_NOT_FOUND 196 
#define  RPC_S_INTERNAL_ERROR 195 
#define  RPC_S_INVALID_ASYNC_CALL 194 
#define  RPC_S_INVALID_ASYNC_HANDLE 193 
#define  RPC_S_INVALID_AUTH_IDENTITY 192 
#define  RPC_S_INVALID_BINDING 191 
#define  RPC_S_INVALID_BOUND 190 
#define  RPC_S_INVALID_ENDPOINT_FORMAT 189 
#define  RPC_S_INVALID_NAF_ID 188 
#define  RPC_S_INVALID_NAME_SYNTAX 187 
#define  RPC_S_INVALID_NETWORK_OPTIONS 186 
#define  RPC_S_INVALID_NET_ADDR 185 
#define  RPC_S_INVALID_OBJECT 184 
#define  RPC_S_INVALID_RPC_PROTSEQ 183 
#define  RPC_S_INVALID_STRING_BINDING 182 
#define  RPC_S_INVALID_STRING_UUID 181 
#define  RPC_S_INVALID_TAG 180 
#define  RPC_S_INVALID_TIMEOUT 179 
#define  RPC_S_INVALID_VERS_OPTION 178 
#define  RPC_S_MAX_CALLS_TOO_SMALL 177 
#define  RPC_S_NAME_SERVICE_UNAVAILABLE 176 
#define  RPC_S_NOTHING_TO_EXPORT 175 
#define  RPC_S_NOT_ALL_OBJS_UNEXPORTED 174 
#define  RPC_S_NOT_LISTENING 173 
#define  RPC_S_NO_BINDINGS 172 
#define  RPC_S_NO_CALL_ACTIVE 171 
#define  RPC_S_NO_CONTEXT_AVAILABLE 170 
#define  RPC_S_NO_ENDPOINT_FOUND 169 
#define  RPC_S_NO_ENTRY_NAME 168 
#define  RPC_S_NO_MORE_BINDINGS 167 
#define  RPC_S_NO_MORE_MEMBERS 166 
#define  RPC_S_NO_PROTSEQS 165 
#define  RPC_S_NO_PROTSEQS_REGISTERED 164 
#define  RPC_S_OBJECT_NOT_FOUND 163 
#define  RPC_S_OUT_OF_RESOURCES 162 
#define  RPC_S_PROCNUM_OUT_OF_RANGE 161 
#define  RPC_S_PROTOCOL_ERROR 160 
#define  RPC_S_PROTSEQ_NOT_FOUND 159 
#define  RPC_S_PROTSEQ_NOT_SUPPORTED 158 
#define  RPC_S_SERVER_TOO_BUSY 157 
#define  RPC_S_SERVER_UNAVAILABLE 156 
#define  RPC_S_STRING_TOO_LONG 155 
#define  RPC_S_TYPE_ALREADY_REGISTERED 154 
#define  RPC_S_UNKNOWN_AUTHN_LEVEL 153 
#define  RPC_S_UNKNOWN_AUTHN_SERVICE 152 
#define  RPC_S_UNKNOWN_AUTHN_TYPE 151 
#define  RPC_S_UNKNOWN_AUTHZ_SERVICE 150 
#define  RPC_S_UNKNOWN_IF 149 
#define  RPC_S_UNKNOWN_MGR_TYPE 148 
#define  RPC_S_UNSUPPORTED_NAME_SYNTAX 147 
#define  RPC_S_UNSUPPORTED_TRANS_SYN 146 
#define  RPC_S_UNSUPPORTED_TYPE 145 
#define  RPC_S_UUID_NO_ADDRESS 144 
#define  RPC_S_WRONG_KIND_OF_BINDING 143 
#define  RPC_S_ZERO_DIVIDE 142 
#define  RPC_X_BAD_STUB_DATA 141 
#define  RPC_X_BYTE_COUNT_TOO_SMALL 140 
#define  RPC_X_ENUM_VALUE_OUT_OF_RANGE 139 
#define  RPC_X_NO_MORE_ENTRIES 138 
#define  RPC_X_NULL_REF_POINTER 137 
#define  RPC_X_PIPE_CLOSED 136 
#define  RPC_X_PIPE_DISCIPLINE_ERROR 135 
#define  RPC_X_PIPE_EMPTY 134 
#define  RPC_X_SS_CANNOT_GET_CALL_HANDLE 133 
#define  RPC_X_SS_CHAR_TRANS_OPEN_FAIL 132 
#define  RPC_X_SS_CHAR_TRANS_SHORT_FILE 131 
#define  RPC_X_SS_CONTEXT_DAMAGED 130 
#define  RPC_X_SS_HANDLES_MISMATCH 129 
#define  RPC_X_SS_IN_NULL_CONTEXT 128 
 scalar_t__ STATUS_ACCESS_DENIED ; 
 scalar_t__ STATUS_ACCESS_VIOLATION ; 
 scalar_t__ STATUS_ACCOUNT_DISABLED ; 
 scalar_t__ STATUS_ACCOUNT_LOCKED_OUT ; 
 scalar_t__ STATUS_BUFFER_TOO_SMALL ; 
 scalar_t__ STATUS_INSUFF_SERVER_RESOURCES ; 
 scalar_t__ STATUS_INVALID_LOGON_HOURS ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_INVALID_SECURITY_DESCR ; 
 scalar_t__ STATUS_NO_MEMORY ; 
 scalar_t__ STATUS_PASSWORD_EXPIRED ; 
 scalar_t__ STATUS_PASSWORD_MUST_CHANGE ; 
 scalar_t__ STATUS_UNSUCCESSFUL ; 
 scalar_t__ STATUS_WRONG_PASSWORD ; 
 int TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,scalar_t__,char*) ; 

__attribute__((used)) static void test_I_RpcMapWin32Status(void)
{
    LONG win32status;
    RPC_STATUS rpc_status;
    BOOL w2k3_up = FALSE;

    /* Windows 2003 and above return STATUS_UNSUCCESSFUL if given an unknown status */
    win32status = I_RpcMapWin32Status(9999);
    if (win32status == STATUS_UNSUCCESSFUL)
        w2k3_up = TRUE;

    /* On Windows XP-SP1 and below some statuses are not mapped and return
     * the given status
     */
    for (rpc_status = 0; rpc_status < 10000; rpc_status++)
    {
        LONG expected_win32status;
        BOOL missing = FALSE;

        win32status = I_RpcMapWin32Status(rpc_status);
        switch (rpc_status)
        {
        case ERROR_SUCCESS: expected_win32status = ERROR_SUCCESS; break;
        case ERROR_ACCESS_DENIED: expected_win32status = STATUS_ACCESS_DENIED; break;
        case ERROR_INVALID_HANDLE: expected_win32status = RPC_NT_SS_CONTEXT_MISMATCH; break;
        case ERROR_OUTOFMEMORY: expected_win32status = STATUS_NO_MEMORY; break;
        case ERROR_INVALID_PARAMETER: expected_win32status = STATUS_INVALID_PARAMETER; break;
        case ERROR_INSUFFICIENT_BUFFER: expected_win32status = STATUS_BUFFER_TOO_SMALL; break;
        case ERROR_MAX_THRDS_REACHED: expected_win32status = STATUS_NO_MEMORY; break;
        case ERROR_NOACCESS: expected_win32status = STATUS_ACCESS_VIOLATION; break;
        case ERROR_NOT_ENOUGH_SERVER_MEMORY: expected_win32status = STATUS_INSUFF_SERVER_RESOURCES; break;
        case ERROR_WRONG_PASSWORD:  expected_win32status = STATUS_WRONG_PASSWORD; missing = TRUE; break;
        case ERROR_INVALID_LOGON_HOURS: expected_win32status = STATUS_INVALID_LOGON_HOURS; missing = TRUE; break;
        case ERROR_PASSWORD_EXPIRED: expected_win32status = STATUS_PASSWORD_EXPIRED; missing = TRUE; break;
        case ERROR_ACCOUNT_DISABLED: expected_win32status = STATUS_ACCOUNT_DISABLED; missing = TRUE; break;
        case ERROR_INVALID_SECURITY_DESCR: expected_win32status = STATUS_INVALID_SECURITY_DESCR; break;
        case RPC_S_INVALID_STRING_BINDING: expected_win32status = RPC_NT_INVALID_STRING_BINDING; break;
        case RPC_S_WRONG_KIND_OF_BINDING: expected_win32status = RPC_NT_WRONG_KIND_OF_BINDING; break;
        case RPC_S_INVALID_BINDING: expected_win32status = RPC_NT_INVALID_BINDING; break;
        case RPC_S_PROTSEQ_NOT_SUPPORTED: expected_win32status = RPC_NT_PROTSEQ_NOT_SUPPORTED; break;
        case RPC_S_INVALID_RPC_PROTSEQ: expected_win32status = RPC_NT_INVALID_RPC_PROTSEQ; break;
        case RPC_S_INVALID_STRING_UUID: expected_win32status = RPC_NT_INVALID_STRING_UUID; break;
        case RPC_S_INVALID_ENDPOINT_FORMAT: expected_win32status = RPC_NT_INVALID_ENDPOINT_FORMAT; break;
        case RPC_S_INVALID_NET_ADDR: expected_win32status = RPC_NT_INVALID_NET_ADDR; break;
        case RPC_S_NO_ENDPOINT_FOUND: expected_win32status = RPC_NT_NO_ENDPOINT_FOUND; break;
        case RPC_S_INVALID_TIMEOUT: expected_win32status = RPC_NT_INVALID_TIMEOUT; break;
        case RPC_S_OBJECT_NOT_FOUND: expected_win32status = RPC_NT_OBJECT_NOT_FOUND; break;
        case RPC_S_ALREADY_REGISTERED: expected_win32status = RPC_NT_ALREADY_REGISTERED; break;
        case RPC_S_TYPE_ALREADY_REGISTERED: expected_win32status = RPC_NT_TYPE_ALREADY_REGISTERED; break;
        case RPC_S_ALREADY_LISTENING: expected_win32status = RPC_NT_ALREADY_LISTENING; break;
        case RPC_S_NO_PROTSEQS_REGISTERED: expected_win32status = RPC_NT_NO_PROTSEQS_REGISTERED; break;
        case RPC_S_NOT_LISTENING: expected_win32status = RPC_NT_NOT_LISTENING; break;
        case RPC_S_UNKNOWN_MGR_TYPE: expected_win32status = RPC_NT_UNKNOWN_MGR_TYPE; break;
        case RPC_S_UNKNOWN_IF: expected_win32status = RPC_NT_UNKNOWN_IF; break;
        case RPC_S_NO_BINDINGS: expected_win32status = RPC_NT_NO_BINDINGS; break;
        case RPC_S_NO_PROTSEQS: expected_win32status = RPC_NT_NO_PROTSEQS; break;
        case RPC_S_CANT_CREATE_ENDPOINT: expected_win32status = RPC_NT_CANT_CREATE_ENDPOINT; break;
        case RPC_S_OUT_OF_RESOURCES: expected_win32status = RPC_NT_OUT_OF_RESOURCES; break;
        case RPC_S_SERVER_UNAVAILABLE: expected_win32status = RPC_NT_SERVER_UNAVAILABLE; break;
        case RPC_S_SERVER_TOO_BUSY: expected_win32status = RPC_NT_SERVER_TOO_BUSY; break;
        case RPC_S_INVALID_NETWORK_OPTIONS: expected_win32status = RPC_NT_INVALID_NETWORK_OPTIONS; break;
        case RPC_S_NO_CALL_ACTIVE: expected_win32status = RPC_NT_NO_CALL_ACTIVE; break;
        case RPC_S_CALL_FAILED: expected_win32status = RPC_NT_CALL_FAILED; break;
        case RPC_S_CALL_FAILED_DNE: expected_win32status = RPC_NT_CALL_FAILED_DNE; break;
        case RPC_S_PROTOCOL_ERROR: expected_win32status = RPC_NT_PROTOCOL_ERROR; break;
        case RPC_S_UNSUPPORTED_TRANS_SYN: expected_win32status = RPC_NT_UNSUPPORTED_TRANS_SYN; break;
        case RPC_S_UNSUPPORTED_TYPE: expected_win32status = RPC_NT_UNSUPPORTED_TYPE; break;
        case RPC_S_INVALID_TAG: expected_win32status = RPC_NT_INVALID_TAG; break;
        case RPC_S_INVALID_BOUND: expected_win32status = RPC_NT_INVALID_BOUND; break;
        case RPC_S_NO_ENTRY_NAME: expected_win32status = RPC_NT_NO_ENTRY_NAME; break;
        case RPC_S_INVALID_NAME_SYNTAX: expected_win32status = RPC_NT_INVALID_NAME_SYNTAX; break;
        case RPC_S_UNSUPPORTED_NAME_SYNTAX: expected_win32status = RPC_NT_UNSUPPORTED_NAME_SYNTAX; break;
        case RPC_S_UUID_NO_ADDRESS: expected_win32status = RPC_NT_UUID_NO_ADDRESS; break;
        case RPC_S_DUPLICATE_ENDPOINT: expected_win32status = RPC_NT_DUPLICATE_ENDPOINT; break;
        case RPC_S_UNKNOWN_AUTHN_TYPE: expected_win32status = RPC_NT_UNKNOWN_AUTHN_TYPE; break;
        case RPC_S_MAX_CALLS_TOO_SMALL: expected_win32status = RPC_NT_MAX_CALLS_TOO_SMALL; break;
        case RPC_S_STRING_TOO_LONG: expected_win32status = RPC_NT_STRING_TOO_LONG; break;
        case RPC_S_PROTSEQ_NOT_FOUND: expected_win32status = RPC_NT_PROTSEQ_NOT_FOUND; break;
        case RPC_S_PROCNUM_OUT_OF_RANGE: expected_win32status = RPC_NT_PROCNUM_OUT_OF_RANGE; break;
        case RPC_S_BINDING_HAS_NO_AUTH: expected_win32status = RPC_NT_BINDING_HAS_NO_AUTH; break;
        case RPC_S_UNKNOWN_AUTHN_SERVICE: expected_win32status = RPC_NT_UNKNOWN_AUTHN_SERVICE; break;
        case RPC_S_UNKNOWN_AUTHN_LEVEL: expected_win32status = RPC_NT_UNKNOWN_AUTHN_LEVEL; break;
        case RPC_S_INVALID_AUTH_IDENTITY: expected_win32status = RPC_NT_INVALID_AUTH_IDENTITY; break;
        case RPC_S_UNKNOWN_AUTHZ_SERVICE: expected_win32status = RPC_NT_UNKNOWN_AUTHZ_SERVICE; break;
        case EPT_S_INVALID_ENTRY: expected_win32status = EPT_NT_INVALID_ENTRY; break;
        case EPT_S_CANT_PERFORM_OP: expected_win32status = EPT_NT_CANT_PERFORM_OP; break;
        case EPT_S_NOT_REGISTERED: expected_win32status = EPT_NT_NOT_REGISTERED; break;
        case EPT_S_CANT_CREATE: expected_win32status = EPT_NT_CANT_CREATE; break;
        case RPC_S_NOTHING_TO_EXPORT: expected_win32status = RPC_NT_NOTHING_TO_EXPORT; break;
        case RPC_S_INCOMPLETE_NAME: expected_win32status = RPC_NT_INCOMPLETE_NAME; break;
        case RPC_S_INVALID_VERS_OPTION: expected_win32status = RPC_NT_INVALID_VERS_OPTION; break;
        case RPC_S_NO_MORE_MEMBERS: expected_win32status = RPC_NT_NO_MORE_MEMBERS; break;
        case RPC_S_NOT_ALL_OBJS_UNEXPORTED: expected_win32status = RPC_NT_NOT_ALL_OBJS_UNEXPORTED; break;
        case RPC_S_INTERFACE_NOT_FOUND: expected_win32status = RPC_NT_INTERFACE_NOT_FOUND; break;
        case RPC_S_ENTRY_ALREADY_EXISTS: expected_win32status = RPC_NT_ENTRY_ALREADY_EXISTS; break;
        case RPC_S_ENTRY_NOT_FOUND: expected_win32status = RPC_NT_ENTRY_NOT_FOUND; break;
        case RPC_S_NAME_SERVICE_UNAVAILABLE: expected_win32status = RPC_NT_NAME_SERVICE_UNAVAILABLE; break;
        case RPC_S_INVALID_NAF_ID: expected_win32status = RPC_NT_INVALID_NAF_ID; break;
        case RPC_S_CANNOT_SUPPORT: expected_win32status = RPC_NT_CANNOT_SUPPORT; break;
        case RPC_S_NO_CONTEXT_AVAILABLE: expected_win32status = RPC_NT_NO_CONTEXT_AVAILABLE; break;
        case RPC_S_INTERNAL_ERROR: expected_win32status = RPC_NT_INTERNAL_ERROR; break;
        case RPC_S_ZERO_DIVIDE: expected_win32status = RPC_NT_ZERO_DIVIDE; break;
        case RPC_S_ADDRESS_ERROR: expected_win32status = RPC_NT_ADDRESS_ERROR; break;
        case RPC_S_FP_DIV_ZERO: expected_win32status = RPC_NT_FP_DIV_ZERO; break;
        case RPC_S_FP_UNDERFLOW: expected_win32status = RPC_NT_FP_UNDERFLOW; break;
        case RPC_S_FP_OVERFLOW: expected_win32status = RPC_NT_FP_OVERFLOW; break;
        case RPC_S_CALL_IN_PROGRESS: expected_win32status = RPC_NT_CALL_IN_PROGRESS; break;
        case RPC_S_NO_MORE_BINDINGS: expected_win32status = RPC_NT_NO_MORE_BINDINGS; break;
        case RPC_S_CALL_CANCELLED: expected_win32status = RPC_NT_CALL_CANCELLED; missing = TRUE; break;
        case RPC_S_INVALID_OBJECT: expected_win32status = RPC_NT_INVALID_OBJECT; break;
        case RPC_S_INVALID_ASYNC_HANDLE: expected_win32status = RPC_NT_INVALID_ASYNC_HANDLE; missing = TRUE; break;
        case RPC_S_INVALID_ASYNC_CALL: expected_win32status = RPC_NT_INVALID_ASYNC_CALL; missing = TRUE; break;
        case RPC_S_GROUP_MEMBER_NOT_FOUND: expected_win32status = RPC_NT_GROUP_MEMBER_NOT_FOUND; break;
        case RPC_X_NO_MORE_ENTRIES: expected_win32status = RPC_NT_NO_MORE_ENTRIES; break;
        case RPC_X_SS_CHAR_TRANS_OPEN_FAIL: expected_win32status = RPC_NT_SS_CHAR_TRANS_OPEN_FAIL; break;
        case RPC_X_SS_CHAR_TRANS_SHORT_FILE: expected_win32status = RPC_NT_SS_CHAR_TRANS_SHORT_FILE; break;
        case RPC_X_SS_IN_NULL_CONTEXT: expected_win32status = RPC_NT_SS_IN_NULL_CONTEXT; break;
        case RPC_X_SS_CONTEXT_DAMAGED: expected_win32status = RPC_NT_SS_CONTEXT_DAMAGED; break;
        case RPC_X_SS_HANDLES_MISMATCH: expected_win32status = RPC_NT_SS_HANDLES_MISMATCH; break;
        case RPC_X_SS_CANNOT_GET_CALL_HANDLE: expected_win32status = RPC_NT_SS_CANNOT_GET_CALL_HANDLE; break;
        case RPC_X_NULL_REF_POINTER: expected_win32status = RPC_NT_NULL_REF_POINTER; break;
        case RPC_X_ENUM_VALUE_OUT_OF_RANGE: expected_win32status = RPC_NT_ENUM_VALUE_OUT_OF_RANGE; break;
        case RPC_X_BYTE_COUNT_TOO_SMALL: expected_win32status = RPC_NT_BYTE_COUNT_TOO_SMALL; break;
        case RPC_X_BAD_STUB_DATA: expected_win32status = RPC_NT_BAD_STUB_DATA; break;
        case RPC_X_PIPE_CLOSED: expected_win32status = RPC_NT_PIPE_CLOSED; missing = TRUE; break;
        case RPC_X_PIPE_DISCIPLINE_ERROR: expected_win32status = RPC_NT_PIPE_DISCIPLINE_ERROR; missing = TRUE; break;
        case RPC_X_PIPE_EMPTY: expected_win32status = RPC_NT_PIPE_EMPTY; missing = TRUE; break;
        case ERROR_PASSWORD_MUST_CHANGE: expected_win32status = STATUS_PASSWORD_MUST_CHANGE; missing = TRUE; break;
        case ERROR_ACCOUNT_LOCKED_OUT: expected_win32status = STATUS_ACCOUNT_LOCKED_OUT; missing = TRUE; break;
        default:
            if (w2k3_up)
                expected_win32status = STATUS_UNSUCCESSFUL;
            else
                expected_win32status = rpc_status;
        }

        ok(win32status == expected_win32status ||
            broken(missing && win32status == rpc_status),
            "I_RpcMapWin32Status(%d) should have returned 0x%x instead of 0x%x%s\n",
            rpc_status, expected_win32status, win32status,
            broken(missing) ? " (or have returned with the given status)" : "");
    }
}