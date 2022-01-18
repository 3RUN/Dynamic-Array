
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
    {
        a = array_create(var, 2);
    }

    var counter = 0;
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        array_add(var, a, counter);
        counter++;
    }
}

void test_remove_last()
{
    if (!a)
    {
        return;
    }

    if (is_array_not_empty(a) == true)
    {
        array_remove_last(var, a);
    }
}

void test_clear_all()
{
    if (!a)
    {
        return;
    }

    array_clear(a);
}

void test_enumerate()
{
    if (!a)
    {
        return;
    }

    var value = 0;
    array_enumerate_begin(var, a, value) // make sure not to place ';' at the end !
    {
        printf("%.0f\n", (double)value);
    }
    array_enumerate_end(a) // make sure not to place ';' at the end !
}

void test_contains()
{
    if (!a)
    {
        return;
    }

    var element = 5, found = false, value = 0;
    array_enumerate_begin(var, a, value) // make sure not to place ';' at the end !
    {
        if (array_get_element_at(var, a, i) != element)
        {
            continue;
        }

        found = true;
        printf("found at index: %d\n", i + 1);
    }
    array_enumerate_end(a) // make sure not to place ';' at the end !

    if(found == false)
    {
        printf("Number %.0f wasn't found in the array.", (double)element);
    }
}

void on_exit_event()
{
    array_destroy(a);
    a = NULL;
}

void main()
{
    on_exit = on_exit_event;

    on_1 = test_add;
    on_2 = test_remove_last;
    on_3 = test_clear_all;
    on_4 = test_enumerate;
    on_5 = test_contains;

    fps_max = 60;
    warn_level = 6;
    random_seed(0);

    while (!key_esc)
    {
        STRING *help_str = "1-to add 10 elements (0...9)\n2-to remove last item\n3-to clear the whole array\n4-to cycle through all elements\n5-check if array contains number 5";
        draw_text(help_str, 10, 0, COLOR_WHITE);

        if (a)
        {
            DEBUG_VAR(a->capacity, 120);
            DEBUG_VAR(array_get_count(a), 140);
            DEBUG_VAR(is_array_not_empty(a), 160);

            // don't allow to crash when empty
            if (is_array_not_empty(a) == true)
            {
                var last = array_get_last(var, a);
                DEBUG_VAR(last, 200);

                int i = 0;
                for (i = 0; i < array_get_count(a); i++)
                {
                    var num = array_get_element_at(var, a, i);
                    DEBUG_VAR(num, 240 + 20 * i);
                }
            }
        }
        wait(1);
    }
}