
#include <acknex.h>
#include <default.c>
#include <stdio.h>

#define PRAGMA_POINTER

#include "cmd.h"
#include "dynamic_array.h"

array_t *a = NULL;

void test_add()
{
    if (!a)
        a = array_create(int, 2);

    int i = 0;
    for (i = 0; i < 10; i++)
        array_add(int, a, i);
}

void test_remove_last()
{
    if (!a)
        return;

    if (is_array_not_empty(a) == true)
        array_remove_last(int, a);
}

void test_clear_all()
{
    if (!a)
        return;

    array_clear(int, a);
}

void test_enumerate()
{
    if (!a)
        return;

    int value = 0;
    array_enumerate_begin(int, a, value)
    {
        printf("%d\n", (long)value);
    }
    array_enumerate_end(a);
}

void test_contains()
{
    if (!a)
        return;

    int element = 5, found = false;
    array_enumerate_begin(int, a, v)
    {
        if (array_get_element_at(int, a, i) != element)
            continue;

        found = true;
        printf("found at index: %d\n", i + 1);
    }
    array_enumerate_end(a);

    if (found == false)
        printf("Number %.d wasn't found in the array.", (long)element);
}

void test_change_odds()
{
    if (!a)
        return;

    array_enumerate_begin(int, a, v)
    {
        if (v % 2 == true)
            array_set_element_at(int, a, i, 555);
    }
    array_enumerate_end(a);
}

void on_exit_event()
{
    array_destroy(a);
    a = NULL;
}

void test_remove_at()
{
    if (!a)
        return;

    array_remove_element_at(int, a, 2);
}

void test_first()
{
    if (!a)
        return;

    if (!is_array_not_empty(a))
        return;

    error(str_printf(NULL, "First element is: %d", (long)array_get_first(int, a)));
}

void test_last()
{
    if (!a)
        return;

    if (!is_array_not_empty(a))
        return;

    error(str_printf(NULL, "Last element is: %d", (long)array_get_last(int, a)));
}

void main()
{
    on_exit = on_exit_event;

    on_1 = test_add;
    on_2 = test_remove_at;
    on_3 = test_remove_last;
    on_4 = test_clear_all;
    on_5 = test_enumerate;
    on_6 = test_contains;
    on_7 = test_change_odds;
    on_8 = test_first;
    on_9 = test_last;

    fps_max = 60;
    warn_level = 6;
    random_seed(0);

    while (!key_esc)
    {
        STRING *help_str = "1 - add 10 elements into the array\n2 - remove element at index 2 (or last)\n3 - remove last element\n4 - clear the whole array\n5 - enumerate the array\n6 - check if array contains element 5\n7 - change odd numbers to 555\n8 - return first element\n9 - return last element";
        draw_text(help_str, 64, 0, COLOR_WHITE);

        if (a)
        {
            DEBUG_VAR(a->capacity, 120);
            DEBUG_VAR(array_get_count(a), 140);
            DEBUG_VAR(is_array_not_empty(a), 160);

            if (is_array_not_empty(a))
            {
                DEBUG_VAR(array_get_last(int, a), 200);

                int i = 0;
                for (i = 0; i < array_get_count(a); i++)
                    DEBUG_VAR(array_get_element_at(int, a, i), 240 + 20 * i);
            }
        }
        wait(1);
    }
}