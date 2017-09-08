
//  AWbase64.c
//  AirWatch
//
//  Created by jjmanton on 3/7/13.

// Credit http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c

/*
 Copyright © 2016 VMware, Inc. All rights reserved.
 This product is protected by copyright and intellectual property laws in the United States and other countries as well as by international treaties.
 AirWatch products may be covered by one or more patents listed at http://www.vmware.com/go/patents.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static const char  table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

char* build_decoding_table();

char *aw_base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length)
{
    
    *output_length = (((input_length - 1) / 3) * 4 + 4) + 1;
    
    char *encoded_data = calloc(*output_length, sizeof(char));
    if (encoded_data == NULL) return NULL;
    
    for (int i = 0, j = 0; i < input_length;) {
        
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;
        
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        
        encoded_data[j++] = table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = table[(triple >> 0 * 6) & 0x3F];
    }
    
    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 2 - i] = '=';
    
    return encoded_data;
}


unsigned char *aw_base64_decode(const char *data,
                             size_t input_length,
                             size_t *output_length)
{
    
    if (decoding_table == NULL) {
        char* decodedTable = build_decoding_table();
        if (decodedTable == NULL) {
            return NULL;
        }
        decoding_table = decodedTable;
    }
    
    
    if (input_length % 4 != 0) return NULL;
    
    *output_length = (input_length / 4 * 3) + 1;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
    
    unsigned char *decoded_data = calloc(*output_length, sizeof(unsigned char));
    if (decoded_data == NULL) return NULL;
    
    for (int i = 0, j = 0; i < input_length;) {
        
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        
        uint32_t triple = (sextet_a << 3 * 6)
            + (sextet_b << 2 * 6)
            + (sextet_c << 1 * 6)
            + (sextet_d << 0 * 6);
        
        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    
    return decoded_data;
}


char* build_decoding_table()
{
    char* tableForDecoding = malloc(256);
    if (tableForDecoding == NULL) {
        return NULL;
    }
    for (int i = 0; i < 0x40; i++)
        tableForDecoding[table[i]] = i;
    
    return tableForDecoding;
}


void base64_cleanup()
{
    free(decoding_table);
}
