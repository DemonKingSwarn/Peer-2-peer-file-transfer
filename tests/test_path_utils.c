#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../lib/path_utils.h"

void test_get_filename() {
    printf("Testing get_filename...\n");
    assert(strcmp(get_filename("/home/user/file.txt"), "file.txt") == 0);
    assert(strcmp(get_filename("file.txt"), "file.txt") == 0);
    assert(strcmp(get_filename("/file.txt"), "file.txt") == 0);
    assert(strcmp(get_filename("/home/user/über/file.txt"), "file.txt") == 0);
    assert(strcmp(get_filename("/home/user/你好.txt"), "你好.txt") == 0);
    printf("Passed.\n");
}

void test_get_directory() {
    printf("Testing get_directory...\n");
    
    char* d1 = get_directory("/home/user/file.txt");
    assert(strcmp(d1, "/home/user") == 0);
    free(d1);

    char* d2 = get_directory("file.txt");
    assert(strcmp(d2, ".") == 0);
    free(d2);

    char* d3 = get_directory("/file.txt");
    assert(strcmp(d3, "/") == 0);
    free(d3);

    char* d4 = get_directory("/home/user/über/file.txt");
    assert(strcmp(d4, "/home/user/über") == 0);
    free(d4);

    printf("Passed.\n");
}

void test_unsafe_chars() {
    printf("Testing has_unsafe_chars...\n");
    assert(has_unsafe_chars("normal.txt") == 0);
    assert(has_unsafe_chars("über.txt") == 0); // Extended ASCII/UTF-8 > 127 should be safe by our logic (only < 32 check)
    
    char bad[] = "bad\nfile.txt";
    assert(has_unsafe_chars(bad) == 1);
    
    printf("Passed.\n");
}

int main() {
    test_get_filename();
    test_get_directory();
    test_unsafe_chars();
    printf("All tests passed!\n");
    return 0;
}
