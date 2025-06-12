#include <acknex.h>
#include <default.c>

#define PRAGMA_POINTER

#include "cmd.h"
#include "dynamic_array.h"

Array *array;

int find(Array *array, void *item)
{
    if (!array || !item)
        return -1;

    return array_find(array, item);
}

void test_add()
{
    if (!array)
        return;

    array_add(array, 55);
}

void test_insert()
{
    if (!array)
        return;

    int index = 1, element = 11;

    if (is_valid_index(array, index))
        array_insert_at(array, index, element);
}

void test_remove()
{
    if (!array)
        return;

    if (is_array_empty(array))
        return;

    array_remove_last(array);
}

void test_clear()
{
    if (!array)
        return;

    if (is_array_empty(array))
        return;

    array_clear(array);
}

void test_swap()
{
    if (!array)
        return;

    if (is_array_empty(array))
        return;

    array_swap(array, 0, array->size - 1);
}

void test_change()
{
    if (!array)
        return;

    int index = 3, element = 555;

    if (is_valid_index(array, index))
        array_change_at(int, array, index, element);
}

void main()
{
    on_1 = test_add;
    on_2 = test_insert;
    on_3 = test_remove;
    on_4 = test_swap;
    on_5 = test_clear;
    on_6 = test_change;

    fps_max = 60;
    warn_level = 6;

    array = array_create(int);

    int i = 0;
    for (i = 0; i < 5; i++)
        array_add(array, i);

    while (!key_esc)
    {
        draw_text("1 - to add 55 at the end\n2 - to insert 11 at index 1\n3 - to remove last element\n4 - to swap first and last elements\n5 - to clear\n6 - to change element at index 3 to 555", 100, 100, COLOR_WHITE);
        draw_text(str_printf(NULL, "size is=%d; capacity is=%d; is_empty=%d;", (long)array_size(array), (long)array_capacity(array), (long)is_array_empty(array)), 10, 0, COLOR_RED);

        if (find(array, 3) != -1)
            draw_text(str_printf(NULL, "number 3 was found at index %d", (long)find(array, 3)), 10, 20, COLOR_RED);
        else
            draw_text("number 3 wasn't found", 10, 20, COLOR_RED);

        if (!is_array_empty(array))
        {
            draw_text(str_printf(NULL, "first %d", (long)array_first(int, array)), 10, 40, COLOR_RED);
            draw_text(str_printf(NULL, "last %d", (long)array_last(int, array)), 10, 60, COLOR_RED);
        }

        for (i = 0; i < array_size(array); i++)
            DEBUG_VAR(array_get_at(int, array, i), 100 + 20 * i);

        wait(1);
    }

    array_destroy(&array);
}