//value type
#define NUM     (unsigned char)0x01
#define STR     (unsigned char)0x02
#define ARR     (unsigned char)0x03
#define OBJ     (unsigned char)0x04
#define NUL     (unsigned char)0x05
#define BOOL    (unsigned char)0x06

//error type
#define ERRKEY  1
#define ERRVAL  2
#define ERRJSN  3

//Use when distinguishing if it is arr node or obj node (it = struct json_node)
#define ARRNODE 1
#define OBJNODE 2
