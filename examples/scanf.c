/*
 * Copyright (c) 2020 Lucas Müller
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <string.h>

#include "libjscon.h"

/* { "a": 1, "b": 300000000, "c": "hello", "d": {"e": "nest"}} */
#define JSON_TEXT "{\"a\":1,\"b\":300000000,\"c\":\"hello\",\"d\":{\"e\":\"nest\"}}"


int main(void)
{
    int a = 0;
    long b = 0;
    char c[25];
    char d[100];

    fprintf(stderr, "a:%p\nb:%p\nc:%p\nd:%p\n\n", (void*)&a, (void*)&b, (void*)c, (void*)d);
    jscon_scanf(JSON_TEXT, "%d[a]%ld[b]%s[c]%S[d]", &a, &b, c, d);

    char output[256];
    snprintf(output, 255, "{\"a\":%d,\"b\":%ld,\"c\":\"%s\",\"d\":%s}", a, b, c, d);

    printf("Resulting string is:\n%s\n" \
           "Expected string is:\n%s\n", 
           JSON_TEXT, output);

    if (0 != strcmp(JSON_TEXT, output)){
        printf("Strings don't match\n");
    } else {
        printf("Strings match\n");
    }
}

