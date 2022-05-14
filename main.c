
#include <acknex.h>
#include <default.c>
#include <stdio.h>

#define PRAGMA_POINTER

#include "cmd.h"
#include "dynamic_array.h"

typedef struct Num
{
    var a;
} Num;

Num odd;

array_t *array = NULL;

void test_add()
{
    if (!array)
    {
        array = array_create(Num *, 2);
    }

    int i = 0;
    for (i = 0; i < 10; i++)
    {
        Num *n = sys_malloc(sizeof(Num));
        n->a = i;
        array_add(Num *, array, n);
    }
}

void test_remove_last()
{
    if (!array)
    {
        return;
    }

    if (is_array_not_empty(array) == true)
    {
        array_remove_last(Num *, array);
    }
}

void test_clear_all()
{
    if (!array)
    {
        return;
    }

    array_clear(Num *, array);
}

void test_enumerate()
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(Num *, array, v)
    {
        if (v)
        {
            printf("%.0f\n", (double)v->a);
        }
    }
    array_enumerate_end(array);
}

void test_contains()
{
    if (!array)
    {
        return;
    }

    var element = 5, found = false;
    array_enumerate_begin(Num *, array, v)
    {
        Num *n = array_get_element_at(Num *, array, i);
        if (n->a != element)
        {
            continue;
        }

        found = true;
        printf("found at index: %d\n", i + 1);
    }
    array_enumerate_end(array);

    if (found == false)
    {
        printf("Number %.0f wasn't found in the array.", (double)element);
    }
}

void test_change_odds()
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(Num *, array, v)
    {
        if (v)
        {
            if (v->a % 2 == true)
            {
                array_set_element_at(Num*, array, i, &odd);
            }
        }
    }
    array_enumerate_end(array);
}

void test_free()
{
    if (!array)
    {
        return;
    }

    array_clear(Num *, array);
    array_destroy(array);
    array = NULL;
}

void on_exit_event()
{
    test_free();
}

void main()
{
    on_exit = on_exit_event;

    on_1 = test_add;
    on_2 = test_remove_last;
    on_3 = test_clear_all;
    on_4 = test_enumerate;
    on_5 = test_contains;
    on_6 = test_change_odds;

    fps_max = 60;
    warn_level = 6;
    random_seed(0);

    odd.a = 555;

    while (!key_esc)
    {
        STRING *help_str = "1-to add 10 elements (0...9)\n2-to remove last item\n3-to clear the whole array\n4 - to cycle through all elements\n5 - check if array contains number 5\n6 - change all odd numbers to 555";
        draw_text(help_str, 10, 0, COLOR_WHITE);

        if (array)
        {
            DEBUG_VAR(array->capacity, 120);
            DEBUG_VAR(array_get_count(array), 140);
            DEBUG_VAR(is_array_not_empty(array), 160);

            // don't allow to crash when empty
            if (is_array_not_empty(array) == true)
            {
                Num *last = array_get_last(Num *, array);
                DEBUG_VAR(last->a, 200);

                int i = 0;
                for (i = 0; i < array_get_count(array); i++)
                {
                    Num *n = array_get_element_at(Num *, array, i);
                    DEBUG_VAR(n->a, 240 + 20 * i);
                }
            }
        }
        wait(1);
    }
}