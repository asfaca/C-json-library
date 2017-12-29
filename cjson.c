#include "cjsonhead.h"
#include "cjsontype.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    struct json_obj_head *json = cjson_parse("sample.json");

    return 0;
}

//check validity of json file.
int valid(char *json, int size) {
    int fp;
    int stack[size/2];
    for(fp = 0; fp < size; fp++) {
        //implement...
    }
}

//use stack?
struct json_obj_head* __parse(char *json, int size) {
    struct json_obj_head *cjson = NULL;
    int i, key_start, key_end;
    cjson = (struct json_obj_head *)malloc(sizeof(struct json_obj_head));
    if (cjson == NULL) {
        printf("ERR : malloc json_obj_head error\n");
        return NULL;
    }

    for(i = 1; i < size; i++) {
        if (json[i] == "\"")
    }

    return cjson;
}

//open json file, parse and convert json to C data structure.
struct json_obj_head* cjson_parse(char *path) {
    /*  
        open json file
        and check error
    */
    char *json = NULL;
    int fd;
    struct stat fs;
    fd = open(path, O_RDONLY);
    if (fd <= 0) {
        printf("ERR : open\n");
        return NULL;
    }

    if (fstat(fd, &fs) < 0) {
        printf("ERR : fstat\n");
        return NULL;
    }

    json = (char*)malloc(sizeof(char) * (fs.st_size + 1));
    if (json == NULL) {
        printf("ERR : malloc\n");
        return NULL;
    }
    if (read(fd, json, fs.st_size) < 0) {
        printf("ERR : read\n");
        return NULL;
    }
    
    /*  
        set stack to hold brace and check validity of json file 
        check {, }, ", ", [, ]
    */
    if (invalid(json, fs.st_size)) {
        printf("ERR : invalid json file\n");
        return NULL;
    }

    /*  
        parse json
        to struct in C
        USE stack to check brace number
        if braces are not match, return err
    */
    return __parse(json, fs.st_size);
}