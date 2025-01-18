#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <emscripten/emscripten.h>

// extern bool EMSCRIPTEN_KEEPALIVE byte_as_bin(char b)
// {
//     for (int i = 0; i < 8; i++)
//     {
//         printf("%d", (b >> (7 - i)) & 1);
//     }
//     printf("\n");

//     return true;
// }

#define DUMB_MIN(a, b) (a < b ? a : b)

typedef enum NumericType
{
    HEXADECIMAL = 0, // Base 16
    DECIMAL,         // Base 10
    OCTAL,           // Base 7
    BINARY,          // Base 2
    NUMERIC_TYPES_LENGTH
} NumericType;

extern const char *EMSCRIPTEN_KEEPALIVE numeric_type_as_string(NumericType type)
{
    switch (type)
    {
    case HEXADECIMAL:
        return "hexadecimal";
        break;
    case DECIMAL:
        return "decimal";
        break;
    case OCTAL:
        return "octal";
        break;
    case BINARY:
        return "binary";
        break;
    default:
        return "unknown numeric type, cannot convert to string";
        break;
    }
}

#define RESULT_BUFFER_SIZE 1024 // NOTE: at somepoint it would be good to enable arbitarily long results
typedef struct Response
{
    char buffer[RESULT_BUFFER_SIZE];
    int status;
} Response;

// ResponseSetError(Response *resp, const char *message)
// 
void ResponseSetError(Response *resp, const char *message)
{
    resp->status = -1;
    
    size_t nChars = DUMB_MIN(strlen(message), RESULT_BUFFER_SIZE - 1);
    
    memset(resp->buffer, 0, RESULT_BUFFER_SIZE);
    strncpy(resp->buffer, message, nChars);
}

Response convert_numeric_types(NumericType inputType, NumericType outputType, char *input)
{
    Response resp;
    memset(resp.buffer, 0, RESULT_BUFFER_SIZE);

    int nChars = snprintf(resp.buffer, RESULT_BUFFER_SIZE, "selected intput type: %s; selected output type: %s; input: %s", numeric_type_as_string(inputType), numeric_type_as_string(outputType), input);
    if (nChars <= 0)
    {
        ResponseSetError(&resp, "something went wrong... probably sprintf being a silly...");
        return resp;
    }

    return resp;
}

extern EMSCRIPTEN_KEEPALIVE Response* create_response()
{
    Response *resp = (Response *)malloc(sizeof(Response));
    memset(resp->buffer, 0, RESULT_BUFFER_SIZE);
    resp->status = 0;
    return resp;
}

extern EMSCRIPTEN_KEEPALIVE void free_response(Response *resp)
{
    free(resp);
}

extern EMSCRIPTEN_KEEPALIVE void convert_numeric_types_js(Response *resp, NumericType inputType, NumericType outputType, char *input)
{
    *resp = convert_numeric_types(inputType, outputType, input);
}
