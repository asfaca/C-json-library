#include "cjsonhead.h"
#include "cjsontype.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void debug_print(struct json_head *json) {

}


int main(void) {
    struct json_head *json = cjson_parse("sample2.json");
    
    printf("%s\n", json->head->key);
    
    return 0;
}

//check validity of json file.
int cjson_invalid(char *json, int size) {
    int fp;
    int stack[size/2];
    for(fp = 0; fp < size; fp++) {
        //implement...
    }
    //if valid...
    return 0;
}

void cjson_check_val_type(char *json, int *index, unsigned char *type) {
    (*index)++;
    while(1) {
        if (json[*index] == '\"') {
            *type = STR;
            return;
        }
        else if (json[*index] == '{') {
            *type = OBJ;
            return;
        }
        else if (json[*index] == '[') {
            *type = ARR;
            return;
        }
        else if (json[*index] >= 48 && json[*index] <= 57) {
            *type = NUM;
            return;
        }
        else if (json[*index] == 'n') {
            *type = NUL;
            return;
        }
        else if (json[*index] == 'f' || json[*index] == 't') {
            *type = BOOL;
            return;
        }
        else
            (*index)++;
    }
}

void cjson_make_common_val(char *json, struct json_head *cjson, int *index, int node_type,
                       void (*func)(char *, struct json_node *, int *)) {
    func(json, cjson->tail, index);
    if (node_type == ARRNODE) {
        cjson->tail->index = cjson->len++;
    }
}

void cjson_make_numval(char *json, struct json_node *key, int *index) {
    int start = *index, end;
    char *temp = NULL;
    key->val_type = NUM;

    while(1) {
        if (json[*index] >= 48 && json[*index] <= 57) {
            (*index)++;
        }
        else {
            end = *index;
            (*index)--;
            break;
        }
    }
    temp = (char*)malloc(sizeof(end - start + 1));
    memcpy(temp, &json[start], end - start);
    temp[end-start] = '\0';

    if (strchr(temp, '.'))
        key->val_num_double = atof(temp);
    else 
        key->val_num_int = atoi(temp);
}


void cjson_make_strval(char *json, struct json_node *key, int *index) {
    int start = ++(*index), end;
    struct json_str_head *str = (struct json_str_head*)malloc(sizeof(struct json_str_head));

    while(1) {
        if (json[*index] == '\"') {
            json[*index] = '\0';
            end = *index;
            str->str = &json[start];
            str->len = end - start;
            key->val_str = str;
            key->val_type = STR;
            return;
        }
        (*index)++;

    }
}

void cjson_make_nulval(char *json, struct json_node *key, int *index) {
    key->val_type = NUL;
}

void cjson_make_boolval(char *json, struct json_node *key, int *index) {
    key->val_type = BOOL;
    if (json[*index] == 't') {
        key->val_bool = 0x01;
        (*index) += 3;
        return;
    }
    else {
        key->val_bool = 0x00;
        (*index) += 4;
        return;
    }
}


//Must be debugged...
void cjson_make_json_node(char *json, struct json_head *cjson, int *index, int node_type) {
    int k_start;
    struct json_node *keynode = NULL;

    //mem allocate for json_node.
    keynode = (struct json_node *)malloc(sizeof(struct json_node));
    if (keynode == NULL) {
        printf("ERR : json_node malloc error.\n");
        return;
    }
    memset(keynode, 0, sizeof(struct json_node));
    
    //set key fields (for object node)
    if (node_type == OBJNODE) {
        k_start = ++(*index);
        while(1) {
            if (json[*index] == '\"') {
                json[*index] = '\0';
                break;
            }
            (*index)++;
        }
        keynode->key = &json[k_start];
    }

    //set link between obj head and node. 
    if (cjson->head == NULL) {
        cjson->head = keynode;
        cjson->tail = keynode;
    }
    else {
        cjson->tail->next = keynode;
        keynode->prev = cjson->tail;
        cjson->tail = keynode;
    }
}

void cjson_make_arrval(char *json, struct json_node *key, int *index) {
    unsigned char type;
    struct json_head *arr_head = (struct json_head *)malloc(sizeof(struct json_head));
    arr_head->len = 0;
    arr_head->head = NULL;
    arr_head->tail = NULL;
    key->val_arr = arr_head;

    (*index)++;
    while(1) {
        if (json[*index] == ']') {
            return;
        }
        else if (json[*index] == ' ' || json[*index] == ',') {
            (*index)++;
            continue;
        }
        else {
            cjson_make_json_node(json, arr_head, index, ARRNODE);
            cjson_check_val_type(json, index, &type);

            if (type == NUM) {
                //cjson_make_numval(json, arr_head, index, ARRNODE);
                cjson_make_common_val(json, arr_head, index, ARRNODE, cjson_make_numval);
            }
            else if (type == STR) {
                //cjson_make_strval(json, arr_head, index);
                cjson_make_common_val(json, arr_head, index, ARRNODE, cjson_make_strval);
            }
            else if (type == OBJ) {
                //how to increase INDEX of ARR?
                arr_head->tail->val_obj = (struct json_head*)malloc(sizeof(struct json_head));
                cjson_make_obj(json, arr_head->tail->val_obj, index);
                arr_head->tail->index = arr_head->len++;
            }
            else if (type == ARR) {
                //how to increase INDEX of ARR?
                cjson_make_arrval(json, arr_head->tail, index);
                arr_head->tail->index = arr_head->len++;
            }
            else if (type == NUL) {
                //cjson_make_nulval(json, arr_head, index);
                cjson_make_common_val(json, arr_head, index, ARRNODE, cjson_make_nulval);
            }
            else if (type == BOOL) {
                //cjson_make_boolval(json, arr_head, index);
                cjson_make_common_val(json, arr_head, index, ARRNODE, cjson_make_boolval);
            }
        }
        (*index)++;
    }
}

/* call chain - object maker */
void cjson_make_obj(char *json, struct json_head *cjson, int *index) {
    unsigned char type;
    
    /* init json_head */
    cjson->len = 0;
    cjson->head = NULL;
    cjson->tail = NULL;
    
    while (1) {    
        //make key node.
        if (json[*index] == '\"') {
            cjson_make_json_node(json, cjson, index, OBJNODE);
        }
        else if (json[*index] == ':') {
            cjson_check_val_type(json, index, &type);
            //make value node for valid type.
            if (type == NUM) {
                cjson_make_common_val(json, cjson, index, OBJNODE, cjson_make_numval);
            }
            else if (type == STR) {
                cjson_make_common_val(json, cjson, index, OBJNODE, cjson_make_strval);
            }
            else if (type == OBJ) {
                cjson->tail->val_obj = (struct json_head*)malloc(sizeof(struct json_head));
                cjson_make_obj(json, cjson->tail->val_obj, index);
            }
            else if (type == ARR) {
                cjson_make_arrval(json, cjson->tail, index);
            }
            else if (type == NUL) {
                cjson_make_common_val(json, cjson, index, OBJNODE, cjson_make_nulval);
            }
            else if (type == BOOL) {
                cjson_make_common_val(json, cjson, index, OBJNODE, cjson_make_boolval);
            }
        }
        else if (json[*index] == ',') {
            (*index)++;
            continue;
        }
        else if (json[*index] == '}') {
            return;
        }
        (*index)++;
    }
}

/* 
    use stack and call chain...
    ex) whenever encountering brace {, call function which makes obj struct
        whenever encountering double quotation ", call function which makes key node struct...
*/
struct json_head* __parse(char *json) {
    int i = 1;
    struct json_head *cjson = (struct json_head*)malloc(sizeof(struct json_head));
    cjson_make_obj(json, cjson , &i);
    return cjson;
}

//open json file, parse and convert json to C data structure.
struct json_head* cjson_parse(char *path) {
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
    return __parse(json);
}