#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef char ShortString[256];

typedef enum {
    KIND_SIGNED,
    KIND_UNSIGNED,
    KIND_FLOATING,
    N_OF_KINDS
} Type_kind_enum;

typedef struct {
    const char * max_type;
} Type_kind_info;

Type_kind_info type_kind_info[N_OF_KINDS] = {
    [KIND_SIGNED]   = {.max_type = "int64_t"},
    [KIND_UNSIGNED] = {.max_type = "uint64_t"},
    [KIND_FLOATING] = {.max_type = "long double"},
};

typedef enum {
    TYPE_I64,
    TYPE_I32,
    TYPE_I16,
    TYPE_I8,
    TYPE_U64,
    TYPE_U32,
    TYPE_U16,
    TYPE_U8,
    TYPE_LDBL,
    TYPE_DBL,
    TYPE_FLT,
    N_OF_TYPES
} Type_enum;

typedef struct {
    const char * alias;
    Type_kind_enum kind;
    const char * ctype;
    const char * val_min;
    const char * val_max;
} Type;

Type types[N_OF_TYPES] = {
    [TYPE_I64]  = {.alias = "i64",  .kind = KIND_SIGNED,   .ctype = "int64_t",     .val_min = "INT64_MIN", .val_max = "INT64_MAX"},
    [TYPE_I32]  = {.alias = "i32",  .kind = KIND_SIGNED,   .ctype = "int32_t",     .val_min = "INT32_MIN", .val_max = "INT32_MAX"},
    [TYPE_I16]  = {.alias = "i16",  .kind = KIND_SIGNED,   .ctype = "int16_t",     .val_min = "INT16_MIN", .val_max = "INT16_MAX"},
    [TYPE_I8]   = {.alias = "i8",   .kind = KIND_SIGNED,   .ctype = "int8_t",      .val_min = "INT8_MIN",  .val_max = "INT8_MAX"},
    [TYPE_U64]  = {.alias = "u64",  .kind = KIND_UNSIGNED, .ctype = "uint64_t",    .val_min = "0",         .val_max = "UINT64_MAX"},
    [TYPE_U32]  = {.alias = "u32",  .kind = KIND_UNSIGNED, .ctype = "uint32_t",    .val_min = "0",         .val_max = "UINT32_MAX"},
    [TYPE_U16]  = {.alias = "u16",  .kind = KIND_UNSIGNED, .ctype = "uint16_t",    .val_min = "0",         .val_max = "UINT16_MAX"},
    [TYPE_U8]   = {.alias = "u8",   .kind = KIND_UNSIGNED, .ctype = "uint8_t",     .val_min = "0",         .val_max = "UINT8_MAX"},
    [TYPE_LDBL] = {.alias = "ldbl", .kind = KIND_FLOATING, .ctype = "long double", .val_min = "-LDBL_MAX", .val_max = "LDBL_MAX"},
    [TYPE_DBL]  = {.alias = "dbl",  .kind = KIND_FLOATING, .ctype = "double",      .val_min = "-DBL_MAX",  .val_max = "DBL_MAX"},
    [TYPE_FLT]  = {.alias = "flt",  .kind = KIND_FLOATING, .ctype = "float",       .val_min = "-FLT_MAX",  .val_max = "FLT_MAX"}
};

typedef enum {
    STATUS_OK,
    STATUS_STREAM_EOF,
    STATUS_STREAM_FERROR,
    STATUS_INPUT_INVALID,
    STATUS_INPUT_OUT_OF_RANGE,
    STATUS_VALUE_OUT_OF_RANGE,
    N_OF_STATUS_CODES
} Status_code_enum;

typedef struct {
    const char * code;
    const char * msg;
} Status_code;

Status_code status_codes[N_OF_STATUS_CODES] = {
    [STATUS_OK]                 = {"MK_STATUS_OK",                 "No error"},
    [STATUS_STREAM_EOF]         = {"MK_STATUS_STREAM_EOF",         "End of stream"},
    [STATUS_STREAM_FERROR]      = {"MK_STATUS_STREAM_FERROR",      "Stream error"},
    [STATUS_INPUT_INVALID]      = {"MK_STATUS_INPUT_INVALID",      "Invalid input"},
    [STATUS_INPUT_OUT_OF_RANGE] = {"MK_STATUS_INPUT_OUT_OF_RANGE", "Input out of range"},
    [STATUS_VALUE_OUT_OF_RANGE] = {"MK_STATUS_VALUE_OUT_OF_RANGE", "Value out of range"}
};

#define FUNC_PREFIX "static inline "

void place_func_header(FILE * target, ShortString func_header) {
    fprintf(target, "%s%s", FUNC_PREFIX, func_header);
}

void place_func_decl(FILE * target, ShortString func_header) {
    place_func_header(target, func_header);
    fprintf(target, ";\n");
}

void place_enum_status(FILE * target) {
    fprintf(target, "typedef enum {\n");
    for (int i = 0; i < N_OF_STATUS_CODES; i++) {
    fprintf(target, "    %s,\n", status_codes[i].code);
    }
    fprintf(target, "} mk_status_t;\n");
}

void place_struct_scanner(FILE * target) {
    fprintf(target, "typedef struct {\n");    
    fprintf(target, "    FILE * istream;\n");
    fprintf(target, "    const char * delim;\n");
    fprintf(target, "    mk_status_t status;\n");
    fprintf(target, "    bool newline_found;\n");
    fprintf(target, "} mk_scanner_t;\n");
}

void place_func_status_get_str(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    switch (status) {\n");
    for (int i = 0; i < N_OF_STATUS_CODES; i++) {
    fprintf(target, "        case %s: return \"%s\";\n", status_codes[i].code, status_codes[i].msg);
    }
    fprintf(target, "        default: return \"Unknown status code\";\n");
    fprintf(target, "    }\n");
    fprintf(target, "}\n");
}

void place_func_parser(FILE * target, Type type, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    %s parsed_value = 0;\n", type_kind_info[type.kind].max_type);
    fprintf(target, "    const char * tkn_start = NULL;\n");
    fprintf(target, "    const char * tkn_end   = NULL;\n");
    fprintf(target, "    \n");
    fprintf(target, "    for (size_t i = 0; string[i] != '\\0'; i++) {\n");
    fprintf(target, "        if (!isspace((unsigned char)string[i])) {\n");
    fprintf(target, "            if (!tkn_start) {tkn_start = string + i;}\n");
    fprintf(target, "            tkn_end = string + i;\n");
    fprintf(target, "        }\n");
    fprintf(target, "    }\n");
    fprintf(target, "    if (tkn_start == NULL) {\n");
    fprintf(target, "        goto INVALID_TOKEN;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    char * parse_end;\n");
    fprintf(target, "    errno = 0;\n");
    fprintf(target, "    parsed_value = ");
    switch (type.kind) {
        case KIND_SIGNED:
        fprintf(target, "strtoll(tkn_start, &parse_end, 0)");
        break;

        case KIND_UNSIGNED:
        fprintf(target, "strtoull(tkn_start, &parse_end, 0)");
        break;

        case KIND_FLOATING:
        fprintf(target, "strtold(tkn_start, &parse_end)");
        break;

        default:
        assert(0 && "Unreachable");
        break;
    }
    fprintf(target, ";\n");
    fprintf(target, "    if (parse_end <= tkn_end) {\n");
    fprintf(target, "        goto INVALID_TOKEN;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    if (errno == ERANGE || ");
    switch (type.kind) {
        case KIND_SIGNED:
        case KIND_FLOATING:
        fprintf(target, "(parsed_value < %s || parsed_value > %s)", type.val_min, type.val_max);
        break;

        case KIND_UNSIGNED:
        fprintf(target, "(parsed_value > %s)", type.val_max);
        break;

        default:
        assert(0 && "Unreachable");
        break;
    }
    fprintf(target, ") {\n");
    fprintf(target, "        goto OUT_OF_RANGE;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    return (%s) parsed_value;\n", type.ctype);
    fprintf(target, "    \n");
    fprintf(target, "    INVALID_TOKEN:\n");
    fprintf(target, "    if (status && *status == %s) {*status = %s;}\n", status_codes[STATUS_OK].code, status_codes[STATUS_INPUT_INVALID].code);
    fprintf(target, "    return 0;\n");
    fprintf(target, "    \n");
    fprintf(target, "    OUT_OF_RANGE:\n");
    fprintf(target, "    if (status && *status == MK_STATUS_OK) {*status = MK_STATUS_VALUE_OUT_OF_RANGE;}\n");
    fprintf(target, "    return 0;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_create(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    mk_scanner_t out;\n");
    fprintf(target, "    out.istream = istream;\n");
    fprintf(target, "    out.status = MK_STATUS_OK;\n");
    fprintf(target, "    out.newline_found = false;\n");
    fprintf(target, "    out.delim = delim;\n");
    fprintf(target, "    return out;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_create_default(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    return mk_scanner_create(stdin, NULL);\n");
    fprintf(target, "}\n");
}

void place_func_scanner_get_status(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    return scanner->status;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_clear_status(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    scanner->status = MK_STATUS_OK;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_set_delim(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    scanner->delim = delim;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_clear_input(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    if (scanner->newline_found) {\n");
    fprintf(target, "        return;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    int c;\n");
    fprintf(target, "    do {\n");
    fprintf(target, "        c = fgetc(scanner->istream);\n");
    fprintf(target, "    } while (c != '\\n' && c != EOF);\n");
    fprintf(target, "    scanner->newline_found = true;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_newline_found(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    return scanner->newline_found;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_get_str(FILE * target, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    if (scanner->status != MK_STATUS_OK) {return 0;}\n");
    fprintf(target, "    if (buffer_length == 0) {\n");
    fprintf(target, "        scanner->status = MK_STATUS_INPUT_OUT_OF_RANGE;\n");
    fprintf(target, "        return 0;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    if (scanner->newline_found) {scanner->newline_found = false;}\n");
    fprintf(target, "    \n");
    fprintf(target, "    size_t token_length = 0;\n");
    fprintf(target, "    while (true) {\n");
    fprintf(target, "        const int c = fgetc(scanner->istream);\n");
    fprintf(target, "        if (c == EOF) {\n");
    fprintf(target, "            if (ferror(scanner->istream)) {goto ERR_FERROR;}\n");
    fprintf(target, "            if (token_length == 0) {goto ERR_EOF_NO_CHAR;}\n");
    fprintf(target, "            break;\n");
    fprintf(target, "        }\n");
    fprintf(target, "        else if (c == '\\n') {\n");
    fprintf(target, "            scanner->newline_found = true;\n");
    fprintf(target, "            break;\n");
    fprintf(target, "        }\n");
    fprintf(target, "        else if (scanner->delim != NULL) {\n");
    fprintf(target, "            if (strchr(scanner->delim, c) != NULL) {\n");
    fprintf(target, "                break;\n");
    fprintf(target, "            }\n");
    fprintf(target, "        }\n");
    fprintf(target, "        else if (token_length > 0 && isspace(c)) {\n");
    fprintf(target, "            break;\n");
    fprintf(target, "        }\n");
    fprintf(target, "        \n");
    fprintf(target, "        if (token_length < buffer_length - 1 || (token_length == 0 && buffer_length == 1)) {\n");
    fprintf(target, "        	buffer[token_length++] = (char) c;\n");
    fprintf(target, "        }\n");
    fprintf(target, "        else {\n");
    fprintf(target, "            scanner->status = MK_STATUS_INPUT_OUT_OF_RANGE;\n");
    fprintf(target, "        }\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    if (buffer_length != 1) {buffer[token_length] = '\\0';}\n");
    fprintf(target, "    return token_length;\n");
    fprintf(target, "    \n");
    fprintf(target, "    ERR_EOF_NO_CHAR:\n");
    fprintf(target, "    scanner->status = MK_STATUS_STREAM_EOF;\n");
    fprintf(target, "    return 0;\n");
    fprintf(target, "    \n");
    fprintf(target, "    ERR_FERROR:\n");
    fprintf(target, "    scanner->status = MK_STATUS_STREAM_FERROR;\n");
    fprintf(target, "    return 0;\n");
    fprintf(target, "}\n");
}

void place_func_scanner_getter(FILE * target, Type type, ShortString header) {
    place_func_header(target, header);
    fprintf(target, " {\n");
    fprintf(target, "    %s parsed_value = 0;\n", type.ctype);
    fprintf(target, "    if (scanner->status != MK_STATUS_OK) {\n");
    fprintf(target, "         return 0;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    char buffer[512] = {0};\n"); // Did you know DBL_MAX has more than 300 digits?
    fprintf(target, "    const size_t tkn_len = mk_scanner_get_str(scanner, buffer, sizeof(buffer));\n");
    fprintf(target, "    if (scanner->status != MK_STATUS_OK) {\n");
    fprintf(target, "        goto TOKENIZATION_ERROR;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    if (tkn_len == 0) {\n");
    fprintf(target, "        goto INVALID_TOKEN;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    parsed_value = mk_parse_%s(buffer, &scanner->status);\n", type.alias);
    fprintf(target, "    if (scanner->status != MK_STATUS_OK) {\n");
    fprintf(target, "        goto PARSING_ERROR;\n");
    fprintf(target, "    }\n");
    fprintf(target, "    \n");
    fprintf(target, "    return parsed_value;\n");
    fprintf(target, "    \n");
    fprintf(target, "    INVALID_TOKEN:\n");
    fprintf(target, "    scanner->status = MK_STATUS_INPUT_INVALID;\n");
    fprintf(target, "    PARSING_ERROR:\n");
    fprintf(target, "    TOKENIZATION_ERROR:\n");
    fprintf(target, "    return 0;\n");
    fprintf(target, "}\n");
}

void generate_source_code_file(FILE * target) {
    ShortString func_status_get_str            = "const char * mk_status_get_message(mk_status_t status)";
    ShortString func_parsers[N_OF_TYPES];
    for (int i = 0; i < N_OF_TYPES; i++) {
        snprintf(func_parsers[i], sizeof(func_parsers), "%s mk_parse_%s(const char * string, mk_status_t * status)", types[i].ctype, types[i].alias);
    }
    ShortString func_scanner_create            = "mk_scanner_t mk_scanner_create(FILE * istream, const char * delim)";
    ShortString func_scanner_create_default    = "mk_scanner_t mk_scanner_create_default(void)";
    ShortString func_scanner_get_status        = "mk_status_t mk_scanner_get_status(mk_scanner_t * scanner)";
    ShortString func_scanner_clear_status      = "void mk_scanner_clear_status(mk_scanner_t * scanner)";
    ShortString func_scanner_set_delim         = "void mk_scanner_set_delim(mk_scanner_t * scanner, const char * delim)";
    ShortString func_scanner_clear_input       = "void mk_scanner_clear_input(mk_scanner_t * scanner)";
    ShortString func_scanner_newline_found     = "bool mk_scanner_newline_found(mk_scanner_t * scanner)";
    ShortString func_scanner_get_str           = "size_t mk_scanner_get_str(mk_scanner_t * scanner, char * buffer, size_t buffer_length)";
    ShortString func_scanner_getters[N_OF_TYPES];
    for (int i = 0; i < N_OF_TYPES; i++) {
        snprintf(func_scanner_getters[i], sizeof(func_scanner_getters[i]), "%s mk_scanner_get_%s(mk_scanner_t * scanner)", types[i].ctype, types[i].alias);
    }

    fprintf(target, "/*\nWARNING:\nSOURCE CODE IS GENERATED FROM A TEMPLATE.\nCHANGES MADE HERE ARE NOT PERSISTENT!\n*/\n");
    fprintf(target, "#ifndef MK_INPAR_H\n");
    fprintf(target, "#define MK_INPAR_H\n");
    fprintf(target, "\n");

    fprintf(target, "#include <stdio.h>\n");
    fprintf(target, "#include <stdlib.h>\n");
    fprintf(target, "#include <stdint.h>\n");
    fprintf(target, "#include <stdbool.h>\n");
    fprintf(target, "#include <ctype.h>\n");
    fprintf(target, "#include <string.h>\n");
    fprintf(target, "#include <float.h>\n");
    fprintf(target, "#include <errno.h>\n");
    fprintf(target, "\n");

    place_enum_status(target);
    fprintf(target, "\n");
    place_struct_scanner(target);
    fprintf(target, "\n");
    
    place_func_decl(target, func_status_get_str);
    fprintf(target, "\n");
    for (int i = 0; i < N_OF_TYPES; i++) {
        place_func_decl(target, func_parsers[i]);
    }
    fprintf(target, "\n");
    place_func_decl(target, func_scanner_create);
    place_func_decl(target, func_scanner_create_default);
    place_func_decl(target, func_scanner_get_status);
    place_func_decl(target, func_scanner_clear_status);
    place_func_decl(target, func_scanner_set_delim);
    place_func_decl(target, func_scanner_clear_input);
    place_func_decl(target, func_scanner_get_str);
    for (int i = 0; i < N_OF_TYPES; i++) {
        place_func_decl(target, func_scanner_getters[i]);
    }
    fprintf(target, "\n");
    
    place_func_status_get_str(target, func_status_get_str);
    fprintf(target, "\n");
    
    for (int i = 0; i < N_OF_TYPES; i++) {
        place_func_parser(target, types[i], func_parsers[i]);
        fprintf(target, "\n");
    }

    place_func_scanner_create(target, func_scanner_create);
    fprintf(target, "\n");
    place_func_scanner_create_default(target, func_scanner_create_default);
    fprintf(target, "\n");
    place_func_scanner_get_status(target, func_scanner_get_status);
    fprintf(target, "\n");
    place_func_scanner_clear_status(target, func_scanner_clear_status);
    fprintf(target, "\n");
    place_func_scanner_set_delim(target, func_scanner_set_delim);
    fprintf(target, "\n");
    place_func_scanner_clear_input(target, func_scanner_clear_input);
    fprintf(target, "\n");
    place_func_scanner_newline_found(target, func_scanner_newline_found);
    fprintf(target, "\n");
    place_func_scanner_get_str(target, func_scanner_get_str);
    fprintf(target, "\n");
    for (int i = 0; i < N_OF_TYPES; i++) {
        place_func_scanner_getter(target, types[i], func_scanner_getters[i]);
        fprintf(target, "\n");
    }
    fprintf(target, "#endif // MK_INPAR_H\n");
}

int main() {
    const char * target_fname = "../mk_inpar.h";
    FILE * target = fopen(target_fname, "w");
    if (target == NULL) {
        printf("Could not open target file!\n");
        return EXIT_FAILURE;
    }

    generate_source_code_file(target);
    fclose(target);

    char command[128] = {0};
    const char * test_output_fname = "compilability_test.o";
    snprintf(command, sizeof(command), "gcc %s -o %s -Wall -Wextra -std=c11", target_fname, test_output_fname);
    int compilation_result = system(command);

    if (compilation_result == 0) {
        printf("Library is compilable. Yay!\n");
        remove(test_output_fname);
    }
    else {
        printf("Can't compile the library! There are errors in the implementation!\n");
    }

    return EXIT_SUCCESS;
}