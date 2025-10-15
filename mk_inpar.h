/*
WARNING:
SOURCE CODE IS GENERATED FROM A TEMPLATE.
CHANGES MADE HERE ARE NOT PERSISTENT!
*/
#ifndef MK_INPAR_H
#define MK_INPAR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <float.h>
#include <errno.h>

typedef enum {
    MK_STATUS_OK,
    MK_STATUS_STREAM_EOF,
    MK_STATUS_STREAM_FERROR,
    MK_STATUS_INPUT_INVALID,
    MK_STATUS_INPUT_OUT_OF_RANGE,
    MK_STATUS_VALUE_OUT_OF_RANGE,
} mk_status_t;

typedef struct {
    FILE * istream;
    const char * delim;
    mk_status_t status;
    bool newline_found;
} mk_scanner_t;

static inline const char * mk_status_get_message(mk_status_t status);

static inline int64_t mk_parse_i64(const char * string, mk_status_t * status);
static inline int32_t mk_parse_i32(const char * string, mk_status_t * status);
static inline int16_t mk_parse_i16(const char * string, mk_status_t * status);
static inline int8_t mk_parse_i8(const char * string, mk_status_t * status);
static inline uint64_t mk_parse_u64(const char * string, mk_status_t * status);
static inline uint32_t mk_parse_u32(const char * string, mk_status_t * status);
static inline uint16_t mk_parse_u16(const char * string, mk_status_t * status);
static inline uint8_t mk_parse_u8(const char * string, mk_status_t * status);
static inline long double mk_parse_ldbl(const char * string, mk_status_t * status);
static inline double mk_parse_dbl(const char * string, mk_status_t * status);
static inline float mk_parse_flt(const char * string, mk_status_t * status);

static inline mk_scanner_t mk_scanner_create(FILE * istream, const char * delim);
static inline mk_scanner_t mk_scanner_create_default(void);
static inline mk_status_t mk_scanner_get_status(mk_scanner_t * scanner);
static inline void mk_scanner_clear_status(mk_scanner_t * scanner);
static inline void mk_scanner_set_delim(mk_scanner_t * scanner, const char * delim);
static inline void mk_scanner_clear_input(mk_scanner_t * scanner);
static inline bool mk_scanner_newline_found(mk_scanner_t * scanner);
static inline size_t mk_scanner_get_str(mk_scanner_t * scanner, char * buffer, size_t buffer_length);
static inline int64_t mk_scanner_get_i64(mk_scanner_t * scanner);
static inline int32_t mk_scanner_get_i32(mk_scanner_t * scanner);
static inline int16_t mk_scanner_get_i16(mk_scanner_t * scanner);
static inline int8_t mk_scanner_get_i8(mk_scanner_t * scanner);
static inline uint64_t mk_scanner_get_u64(mk_scanner_t * scanner);
static inline uint32_t mk_scanner_get_u32(mk_scanner_t * scanner);
static inline uint16_t mk_scanner_get_u16(mk_scanner_t * scanner);
static inline uint8_t mk_scanner_get_u8(mk_scanner_t * scanner);
static inline long double mk_scanner_get_ldbl(mk_scanner_t * scanner);
static inline double mk_scanner_get_dbl(mk_scanner_t * scanner);
static inline float mk_scanner_get_flt(mk_scanner_t * scanner);

static inline const char * mk_status_get_message(mk_status_t status) {
    switch (status) {
        case MK_STATUS_OK: return "No error";
        case MK_STATUS_STREAM_EOF: return "End of stream";
        case MK_STATUS_STREAM_FERROR: return "Stream error";
        case MK_STATUS_INPUT_INVALID: return "Invalid input";
        case MK_STATUS_INPUT_OUT_OF_RANGE: return "Input out of range";
        case MK_STATUS_VALUE_OUT_OF_RANGE: return "Value out of range";
        default: return "Unknown status code";
    }
}

static inline int64_t mk_parse_i64(const char * string, mk_status_t * status) {
    int64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoll(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < INT64_MIN || parsed_value > INT64_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (int64_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline int32_t mk_parse_i32(const char * string, mk_status_t * status) {
    int64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoll(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < INT32_MIN || parsed_value > INT32_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (int32_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline int16_t mk_parse_i16(const char * string, mk_status_t * status) {
    int64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoll(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < INT16_MIN || parsed_value > INT16_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (int16_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline int8_t mk_parse_i8(const char * string, mk_status_t * status) {
    int64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoll(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < INT8_MIN || parsed_value > INT8_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (int8_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline uint64_t mk_parse_u64(const char * string, mk_status_t * status) {
    uint64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoull(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value > UINT64_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (uint64_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline uint32_t mk_parse_u32(const char * string, mk_status_t * status) {
    uint64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoull(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value > UINT32_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (uint32_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline uint16_t mk_parse_u16(const char * string, mk_status_t * status) {
    uint64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoull(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value > UINT16_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (uint16_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline uint8_t mk_parse_u8(const char * string, mk_status_t * status) {
    uint64_t parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtoull(tkn_start, &parse_end, 0);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value > UINT8_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (uint8_t) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline long double mk_parse_ldbl(const char * string, mk_status_t * status) {
    long double parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtold(tkn_start, &parse_end);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -LDBL_MAX || parsed_value > LDBL_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (long double) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline double mk_parse_dbl(const char * string, mk_status_t * status) {
    long double parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtold(tkn_start, &parse_end);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -DBL_MAX || parsed_value > DBL_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (double) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline float mk_parse_flt(const char * string, mk_status_t * status) {
    long double parsed_value = 0;
    const char * tkn_start = NULL;
    const char * tkn_end   = NULL;
    
    for (size_t i = 0; string[i] != '\0'; i++) {
        if (!isspace((unsigned char)string[i])) {
            if (!tkn_start) {tkn_start = string + i;}
            tkn_end = string + i;
        }
    }
    if (tkn_start == NULL) {
        goto INVALID_TOKEN;
    }
    
    char * parse_end;
    errno = 0;
    parsed_value = strtold(tkn_start, &parse_end);
    if (parse_end <= tkn_end) {
        goto INVALID_TOKEN;
    }
    if (errno == ERANGE || (parsed_value < -FLT_MAX || parsed_value > FLT_MAX)) {
        goto OUT_OF_RANGE;
    }
    
    return (float) parsed_value;
    
    INVALID_TOKEN:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_INPUT_INVALID;}
    return 0;
    
    OUT_OF_RANGE:
    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}
    return 0;
}

static inline mk_scanner_t mk_scanner_create(FILE * istream, const char * delim) {
    mk_scanner_t out;
    out.istream = istream;
    out.status = MK_STATUS_OK;
    out.newline_found = false;
    out.delim = delim;
    return out;
}

static inline mk_scanner_t mk_scanner_create_default(void) {
    return mk_scanner_create(stdin, NULL);
}

static inline mk_status_t mk_scanner_get_status(mk_scanner_t * scanner) {
    return scanner->status;
}

static inline void mk_scanner_clear_status(mk_scanner_t * scanner) {
    scanner->status = MK_STATUS_OK;
}

static inline void mk_scanner_set_delim(mk_scanner_t * scanner, const char * delim) {
    scanner->delim = delim;
}

static inline void mk_scanner_clear_input(mk_scanner_t * scanner) {
    if (scanner->newline_found) {
        return;
    }
    int c;
    do {
        c = fgetc(scanner->istream);
    } while (c != '\n' && c != EOF);
    scanner->newline_found = true;
}

static inline bool mk_scanner_newline_found(mk_scanner_t * scanner) {
    return scanner->newline_found;
}

static inline size_t mk_scanner_get_str(mk_scanner_t * scanner, char * buffer, size_t buffer_length) {
    if (scanner->status != MK_STATUS_OK) {return 0;}
    if (buffer_length == 0) {
        scanner->status = MK_STATUS_INPUT_OUT_OF_RANGE;
        return 0;
    }
    
    if (scanner->newline_found) {scanner->newline_found = false;}
    
    size_t token_length = 0;
    while (true) {
        const int c = fgetc(scanner->istream);
        if (c == EOF) {
            if (ferror(scanner->istream)) {goto ERR_FERROR;}
            if (token_length == 0) {goto ERR_EOF_NO_CHAR;}
            break;
        }
        else if (c == '\n') {
            scanner->newline_found = true;
            break;
        }
        else if (scanner->delim != NULL) {
            if (strchr(scanner->delim, c) != NULL) {
                break;
            }
        }
        else if (token_length > 0 && isspace(c)) {
            break;
        }
        
        if (token_length < buffer_length - 1 || (token_length == 0 && buffer_length == 1)) {
        	buffer[token_length++] = (char) c;
        }
        else {
            scanner->status = MK_STATUS_INPUT_OUT_OF_RANGE;
        }
    }
    
    if (buffer_length != 1) {buffer[token_length] = '\0';}
    return token_length;
    
    ERR_EOF_NO_CHAR:
    scanner->status = MK_STATUS_STREAM_EOF;
    return 0;
    
    ERR_FERROR:
    scanner->status = MK_STATUS_STREAM_FERROR;
    return 0;
}

static inline int64_t mk_scanner_get_i64(mk_scanner_t * scanner) {
    int64_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_i64(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline int32_t mk_scanner_get_i32(mk_scanner_t * scanner) {
    int32_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_i32(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline int16_t mk_scanner_get_i16(mk_scanner_t * scanner) {
    int16_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_i16(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline int8_t mk_scanner_get_i8(mk_scanner_t * scanner) {
    int8_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_i8(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline uint64_t mk_scanner_get_u64(mk_scanner_t * scanner) {
    uint64_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_u64(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline uint32_t mk_scanner_get_u32(mk_scanner_t * scanner) {
    uint32_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_u32(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline uint16_t mk_scanner_get_u16(mk_scanner_t * scanner) {
    uint16_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_u16(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline uint8_t mk_scanner_get_u8(mk_scanner_t * scanner) {
    uint8_t parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_u8(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline long double mk_scanner_get_ldbl(mk_scanner_t * scanner) {
    long double parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_ldbl(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline double mk_scanner_get_dbl(mk_scanner_t * scanner) {
    double parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_dbl(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

static inline float mk_scanner_get_flt(mk_scanner_t * scanner) {
    float parsed_value = 0;
    if (scanner->status != MK_STATUS_OK) {
         return 0;
    }
    
    char buffer[512] = {0};
    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));
    if (scanner->status != MK_STATUS_OK) {
        goto TOKENIZATION_ERROR;
    }
    if (tkn_len == 0) {
        goto INVALID_TOKEN;
    }
    
    parsed_value = mk_parse_flt(buffer, &scanner->status);
    if (scanner->status != MK_STATUS_OK) {
        goto PARSING_ERROR;
    }
    
    return parsed_value;
    
    INVALID_TOKEN:
    scanner->status = MK_STATUS_INPUT_INVALID;
    PARSING_ERROR:
    TOKENIZATION_ERROR:
    return 0;
}

#endif // MK_INPAR_H
