// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

/**
 * @file attester.h
 *
 * This file defines the programming interface for application enclaves
 * to access the OE SDK attester functionality for evidence generation.
 *
 */

#ifndef _OE_ATTESTATION_ATTESTER_H
#define _OE_ATTESTATION_ATTESTER_H

#ifdef _OE_HOST_H

#error "The header attester.h is only available for the enclave."

#else // _OE_HOST_H

#include <openenclave/bits/evidence.h>
#include <openenclave/bits/result.h>
#include <openenclave/bits/types.h>

OE_EXTERNC_BEGIN

/**
 * Bit-wise flags passed to oe_get_evidence() function. If this bit is set,
 * the evidence and endorsements will be wrapped with a header containing the
 * format ID.
 */
#define OE_EVIDENCE_FLAGS_EMBED_FORMAT_ID 0x00000001

/**
 * oe_attester_initialize
 *
 * Initializes the attester environment configured for the platform and
 * the calling application.
 * This function is only available in the enclave.
 *
 * This function is idempotent and can be called multiple times without
 * adverse effect.
 *
 * @experimental
 *
 * @retval OE_OK on success.
 * @retval other appropriate error code.
 */
oe_result_t oe_attester_initialize(void);

/**
 * oe_attester_select_format
 *
 * Selects the left-most evidence format from the input list that is supported.
 * This function is only available in the enclave.
 *
 * @experimental
 *
 * @param[in] format_ids Ordered list of evidence format ids from which to
 * select, with descending priority order from left to right.
 * @param[in] format_ids_length The number of entries in the input evidence
 * format id list.
 * @param[out] selected_format_id Pointer to a caller-supplied buffer to
 * hold the selected evidence format id.
 * @retval OE_OK on success.
 * @retval OE_INVALID_PARAMETER At least one of the parameters is invalid.
 * @retval OE_NOT_FOUND if no format id in the input list is supported.
 * @retval other appropriate error code.
 */
oe_result_t oe_attester_select_format(
    const oe_uuid_t* format_ids,
    size_t format_ids_length,
    oe_uuid_t* selected_format_id);

/**
 * oe_get_evidence
 *
 * Generates the evidence for the given format id.
 * This function is only available in the enclave.
 *
 * @experimental
 *
 * @param[in] format_id The format ID of the evidence to be generated.
 * @param[in] flags A bit-wise parameter. Currently there is one bit
 * defined: OE_EVIDENCE_FLAGS_EMBED_FORMAT_ID. If this bit is set,
 * the evidence and endorsements will be wrapped with a header containing
 * the format ID.
 * @param[in] custom_claims The optional custom claims buffer.
 * @param[in] custom_claims_size The number of bytes in the custom claims
 * buffer.
 * @param[in] optional_parameters The optional format-specific input parameters.
 * @param[in] optional_parameters_size The size of optional_parameters in bytes.
 * @param[out] evidence_buffer An output pointer that will be assigned the
 * address of the dynamically allocated evidence buffer.
 * @param[out] evidence_buffer_size A pointer that points to the size of the
 * evidence buffer in bytes.
 * @param[out] endorsements_buffer If not NULL, an output pointer that will be
 * assigned the address of the dynamically allocated endorsements buffer.
 * @param[out] endorsements_buffer_size A pointer that points to the size of the
 * endorsements buffer in bytes.
 * @retval OE_OK The function succeeded.
 * @retval OE_INVALID_PARAMETER At least one of the parameters is invalid.
 * @retval OE_NOT_FOUND The input evidence format id is not supported.
 * @retval other appropriate error code.
 */
oe_result_t oe_get_evidence(
    const oe_uuid_t* format_id,
    uint32_t flags,
    const void* custom_claims,
    size_t custom_claims_size,
    const void* optional_parameters,
    size_t optional_parameters_size,
    uint8_t** evidence_buffer,
    size_t* evidence_buffer_size,
    uint8_t** endorsements_buffer,
    size_t* endorsements_buffer_size);

/**
 * oe_get_attestation_certificate_with_evidence
 *
 * This function generates a self-signed x.509 certificate with embedded
 * evidence generated by an attester plugin for the enclave.
 *
 * @param[in] format_id The format id of the evidence to be generated.
 *
 * @param[in] subject_name a string containing an X.509 distinguished
 * name (DN) for customizing the generated certificate. This name is also used
 * as the issuer name because this is a self-signed certificate
 * See RFC5280 (https://tools.ietf.org/html/rfc5280) for details
 * Example value "CN=Open Enclave SDK,O=OESDK TLS,C=US"
 *
 * @param[in] private_key a private key used to sign this certificate
 * @param[in] private_key_size The size of the private_key buffer
 * @param[in] public_key a public key used as the certificate's subject key
 * @param[in] public_key_size The size of the public_key buffer.
 *
 * @param[out] output_cert a pointer to buffer pointer
 * @param[out] output_cert_size size of the buffer above
 *
 * @return OE_OK on success
 */
oe_result_t oe_get_attestation_certificate_with_evidence(
    const oe_uuid_t* format_id,
    const unsigned char* subject_name,
    uint8_t* private_key,
    size_t private_key_size,
    uint8_t* public_key,
    size_t public_key_size,
    uint8_t** output_cert,
    size_t* output_cert_size);

/**
 * oe_free_evidence
 *
 * Frees the attestation evidence.
 * This function is only available in the enclave.
 *
 * @experimental
 *
 * @param[in] evidence_buffer A pointer to the evidence buffer.
 * @retval OE_OK The function succeeded.
 * @retval other appropriate error code.
 */
oe_result_t oe_free_evidence(uint8_t* evidence_buffer);

/**
 * oe_free_endorsements
 *
 * Frees the generated attestation endorsements.
 * This function is only available in the enclave.
 *
 * @experimental
 *
 * @param[in] endorsements_buffer A pointer to the endorsements buffer.
 * @retval OE_OK The function succeeded.
 * @retval other appropriate error code.
 */
oe_result_t oe_free_endorsements(uint8_t* endorsements_buffer);

/**
 * oe_attester_shutdown
 *
 * Shuts down the attester environment configured for the platform and
 * the calling application.
 * This function is only available in the enclave.
 *
 * This function is idempotent and can be called multiple times without
 * adverse effect.
 *
 * @experimental
 *
 * @retval OE_OK on success.
 * @retval other appropriate error code.
 */
oe_result_t oe_attester_shutdown(void);

OE_EXTERNC_END

#endif // _OE_HOST_H

#endif /* _OE_ATTESTATION_ATTESTER_H */
