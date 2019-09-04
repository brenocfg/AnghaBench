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
typedef  int DWORD ;

/* Variables and functions */
#define  CERT_E_UNTRUSTEDROOT 169 
#define  CRYPT_E_BAD_ENCODE 168 
#define  CRYPT_E_BAD_LEN 167 
#define  CRYPT_E_BAD_MSG 166 
#define  CRYPT_E_DELETED_PREV 165 
#define  CRYPT_E_EXISTS 164 
#define  CRYPT_E_FILE_ERROR 163 
#define  CRYPT_E_HASH_VALUE 162 
#define  CRYPT_E_INVALID_IA5_STRING 161 
#define  CRYPT_E_INVALID_MSG_TYPE 160 
#define  CRYPT_E_INVALID_NUMERIC_STRING 159 
#define  CRYPT_E_INVALID_PRINTABLE_STRING 158 
#define  CRYPT_E_INVALID_X500_STRING 157 
#define  CRYPT_E_ISSUER_SERIALNUMBER 156 
#define  CRYPT_E_MSG_ERROR 155 
#define  CRYPT_E_NOT_CHAR_STRING 154 
#define  CRYPT_E_NOT_FOUND 153 
#define  CRYPT_E_NOT_IN_REVOCATION_DATABASE 152 
#define  CRYPT_E_NO_DECRYPT_CERT 151 
#define  CRYPT_E_NO_KEY_PROPERTY 150 
#define  CRYPT_E_NO_MATCH 149 
#define  CRYPT_E_NO_PROVIDER 148 
#define  CRYPT_E_NO_REVOCATION_CHECK 147 
#define  CRYPT_E_NO_REVOCATION_DLL 146 
#define  CRYPT_E_NO_SIGNER 145 
#define  CRYPT_E_NO_TRUSTED_SIGNER 144 
#define  CRYPT_E_NO_VERIFY_USAGE_CHECK 143 
#define  CRYPT_E_REVOCATION_OFFLINE 142 
#define  CRYPT_E_REVOKED 141 
#define  CRYPT_E_SECURITY_SETTINGS 140 
#define  CRYPT_E_UNEXPECTED_MSG_TYPE 139 
#define  CRYPT_E_UNKNOWN_ALGO 138 
#define  CRYPT_E_VERIFY_USAGE_OFFLINE 137 
 int GetLastError () ; 
#define  NTE_BAD_ALGID 136 
#define  NTE_BAD_KEYSET 135 
#define  NTE_BAD_SIGNATURE 134 
#define  NTE_BAD_UID 133 
#define  NTE_BAD_VER 132 
#define  NTE_NO_KEY 131 
#define  TRUST_E_EXPLICIT_DISTRUST 130 
#define  TRUST_E_NOSIGNATURE 129 
#define  TRUST_E_TIME_STAMP 128 
 char const* WindowsErrorString () ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int) ; 

const char* WinPKIErrorString(void)
{
	static char error_string[64];
	DWORD error_code = GetLastError();

	if (((error_code >> 16) != 0x8009) && ((error_code >> 16) != 0x800B))
		return WindowsErrorString();

	switch (error_code) {
	// See also https://docs.microsoft.com/en-gb/windows/desktop/com/com-error-codes-4
	case NTE_BAD_UID:
		return "Bad UID.";
	case NTE_NO_KEY:
		return "Key does not exist.";
	case NTE_BAD_KEYSET:
		return "Keyset does not exist.";
	case NTE_BAD_ALGID:
		return "Invalid algorithm specified.";
	case NTE_BAD_VER:
		return "Bad version of provider.";
	case NTE_BAD_SIGNATURE:
		return "Invalid Signature.";
	case CRYPT_E_MSG_ERROR:
		return "An error occurred while performing an operation on a cryptographic message.";
	case CRYPT_E_UNKNOWN_ALGO:
		return "Unknown cryptographic algorithm.";
	case CRYPT_E_INVALID_MSG_TYPE:
		return "Invalid cryptographic message type.";
	case CRYPT_E_HASH_VALUE:
		return "The hash value is not correct";
	case CRYPT_E_ISSUER_SERIALNUMBER:
		return "Invalid issuer and/or serial number.";
	case CRYPT_E_BAD_LEN:
		return "The length specified for the output data was insufficient.";
	case CRYPT_E_BAD_ENCODE:
		return "An error occurred during encode or decode operation.";
	case CRYPT_E_FILE_ERROR:
		return "An error occurred while reading or writing to a file.";
	case CRYPT_E_NOT_FOUND:
		return "Cannot find object or property.";
	case CRYPT_E_EXISTS:
		return "The object or property already exists.";
	case CRYPT_E_NO_PROVIDER:
		return "No provider was specified for the store or object.";
	case CRYPT_E_DELETED_PREV:
		return "The previous certificate or CRL context was deleted.";
	case CRYPT_E_NO_MATCH:
		return "Cannot find the requested object.";
	case CRYPT_E_UNEXPECTED_MSG_TYPE:
	case CRYPT_E_NO_KEY_PROPERTY:
	case CRYPT_E_NO_DECRYPT_CERT:
		return "Private key or certificate issue";
	case CRYPT_E_BAD_MSG:
		return "Not a cryptographic message.";
	case CRYPT_E_NO_SIGNER:
		return "The signed cryptographic message does not have a signer for the specified signer index.";
	case CRYPT_E_REVOKED:
		return "The certificate is revoked.";
	case CRYPT_E_NO_REVOCATION_DLL:
	case CRYPT_E_NO_REVOCATION_CHECK:
	case CRYPT_E_REVOCATION_OFFLINE:
	case CRYPT_E_NOT_IN_REVOCATION_DATABASE:
		return "Cannot check certificate revocation.";
	case CRYPT_E_INVALID_NUMERIC_STRING:
	case CRYPT_E_INVALID_PRINTABLE_STRING:
	case CRYPT_E_INVALID_IA5_STRING:
	case CRYPT_E_INVALID_X500_STRING:
	case  CRYPT_E_NOT_CHAR_STRING:
		return "Invalid string.";
	case CRYPT_E_SECURITY_SETTINGS:
		return "The cryptographic operation failed due to a local security option setting.";
	case CRYPT_E_NO_VERIFY_USAGE_CHECK:
	case CRYPT_E_VERIFY_USAGE_OFFLINE:
		return "Cannot complete usage check.";
	case CRYPT_E_NO_TRUSTED_SIGNER:
		return "None of the signers of the cryptographic message or certificate trust list is trusted.";
	case CERT_E_UNTRUSTEDROOT:
		return "The root certificate is not trusted.";
	case TRUST_E_NOSIGNATURE:
		return "Not digitally signed.";
	case TRUST_E_EXPLICIT_DISTRUST:
		return "One of the certificates used was marked as untrusted by the user.";
	case TRUST_E_TIME_STAMP:
		return "The timestamp could not be verified.";
	default:
		static_sprintf(error_string, "Unknown PKI error 0x%08lX", error_code);
		return error_string;
	}
}