#include "cjsonhead.h"
#include "cjsontype.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    struct json_obj_head *json = cjson_parse("./sample.json")

    return 0;
}

//open json file, parse and convert json to C data structure.
struct json_obj_head* cjson_parse(char *path) {
    /*  
        open json file
        and check error
    */
    char *json;
    int fd;
    struct stat *fs;
    if ((fd = open(path, O_RDONLY) <= 0))
        return NULL;
    if (fstat(fd, fs) < 0)
        return NULL;

    json = (char*)malloc(sizeof(char) * (fs->st_size + 1));
    if (read(fd, json, fs->st_size) < 0)
        return NULL;

    /*  set stack to hold brace */


    /*  
        parse json
        to struct in C
        USE stack to check brace number
        if braces are not match, return err
    */
}