#include "cjsonhead.h"
#include "cjsontype.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    struct json_obj_head *json = cjson_parse("sample.json");

    return 0;
}

//check validity of json file.
int cjson_invalid(char *json, int size) {
    int fp;
    int stack[size/2];
    for(fp = 0; fp < size; fp++) {
        //implement...
    }
}

void cjson_make_json_node(char *json, struct json_obj_head *cjson, int *index) {
    int k_start = ++*index, k_end;
    char *keyname = NULL;
    struct json_node *keynode = NULL;

    //mem allocate for json_node.
    keynode = (struct json_node *)malloc(sizeof(struct json_node));
    if (keynode = NULL) {
        printf("ERR : json_node malloc error.\n");
        return;
    }
    memset(keynode, 0, sizeof(struct json_node));
    
    //set key fields
    while(1) {
        if (*index == '\"') {
            k_end = *index;
            break;
        }
        *index++;
    }
    keyname = (char*)malloc(sizeof(k_end - k_start + 1));
    memcpy((char*)keyname, (char*)&json[k_start], k_end - k_start);
    keyname[k_end - k_start] = '\0';
    keynode->key = keyname;

    //set link between obj head and node. 
    if (cjson->head == NULL) {
        cjson->head = keynode;
        cjson->tail = keynode;
        cjson->len++;
    }
    else {
        cjson->tail->next = keynode;
        keynode->prev = cjson->tail;
        cjson->tail = keynode;
    }
}

void cjson_check_val_type(char *json, int *index, char *type) {

}

void cjson_make_numval(char *json, struct json_node *key, int *index) {

}

void cjson_make_strval(char *json, struct json_node *key, int *index) {

}

void cjson_make_arrval(char *json, struct json_node *key, int *index) {

}

void cjson_make_nulval(char *json, struct json_node *key, int *index) {

}

void cjson_make_boolval(char *json, struct json_node *key, int *index) {

}

/* call chain - object maker */
void cjson_make_obj(char *json, struct json_obj_head *cjson, int *index, int size) {
    char type;
    cjson = (struct json_obj_head*)malloc(sizeof(struct json_obj_head));
    if (cjson == NULL) {
        printf("ERR : json_obj_head malloc error\n");
        return;
    }
    /* init json_obj_head */
    cjson->len = 0;
    cjson->head = NULL;
    cjson->tail = NULL;

    while (*index < size) {    
        //make key node.
        if (json[*index] == '\"')
            cjson_make_json_node(json, cjson, index);
        //check : token. if token is :, decide which type of value.
        else if (json[*index] == ':') {
            cjson_check_val_type(json, index, &type);
            //make value node for valid type.
            if (type == NUM) {
                cjson_make_numval(json, cjson->tail, index);
            }
            else if (type == STR) {
                cjson_make_strval(json, cjson->tail, index);
            }
            else if (type == OBJ) {
                cjson_make_obj(json, cjson->tail->val_obj, index, size);
            }
            else if (type == ARR) {
                cjson_make_arrval(json, cjson->tail, index);
            }
            else if (type == NUL) {
                cjson_make_nulval(json, cjson->tail, index);
            }
            else if (type == BOOL) {
                cjson_make_boolval(json, cjson->tail, index);
            }
        }
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
    if (cjson_invalid(json, fs.st_size)) {
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