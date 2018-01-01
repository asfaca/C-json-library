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

/* call chain - object maker */
void cjson_make_obj(char *json, struct json_obj_head *cjson, int *index, int size) {
    cjson = (struct json_obj_head*)malloc(sizeof(struct json_obj_head));
    if (cjson == NULL) {
        printf("ERR : json_obj_head malloc error\n");
        return;
    }
    /* init json_obj_head */
    memset(cjson, 0, sizeof(struct json_obj_head));
    
    while (*index < size) {    
        //make key node.
        if (json[*index] == '\"')
            cjson_make_json_node(json, cjson->next, index, size);
        //check : token. if token is :, decide which type of value.
        else if () {

        }
        //make value node for valid type.

        //check , for continue
        else if (json[*index] == ',') {
            *index++;
            continue;
        }
        //check end brace for exit while loop.
        else if (json[*index] == '}') {
            *index++;
            return;
        }
        //increase i
        *index++;
    }
}

/* 
    use stack and call chain...
    ex) whenever encountering brace {, call function which makes obj struct
        whenever encountering double quotation ", call function which makes key node struct...
*/
struct json_obj_head* __parse(char *json, int size) {

    int i = 1;
    struct json_obj_head *cjson = NULL;
    cjson_make_obj(json, cjson ,&i, size);
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
    if (cJson_invalid(json, fs.st_size)) {
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