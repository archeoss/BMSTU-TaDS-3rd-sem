#ifndef _APARTMENT_H_

#define _APARTMENT_H_

#define ADDRESS_LEN 100
#define SHORT_VALUE 32767
#define INT_VALUE 2147483647

typedef struct
{
    char address[ADDRESS_LEN];
    short square;
    short room_count;
    int square_price;
    short t;
    union type
    {
        struct secondary
        {
            short build_date;
            short owner_count;
            short last_owner_count;
            short was_animal;
        } sec;
        struct primary
        {
            short trim;
        } prim;
    } tp;
} apartment;

typedef struct
{
    int index_orig;
    int square_price;
} apartment_key;

#endif