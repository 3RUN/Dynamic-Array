
#include <acknex.h>
#include <default.c>
#include <stdio.h>

#define PRAGMA_POINTER

#include "cmd.h"
#include "dynamic_array.h"

array_t *a = NULL;

void test_remove()
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

void test_grow()
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

void test_enumerate()
{
    if (!a)
    {
        return;
    }

    var value = 0;
    array_enumerate_begin(var, a, value);
    printf("%.0f\n", (double)value);
    array_enumerate_end(a) // make sure not to place ';' at the end !
}

void on_exit_event()
{
    array_destroy(a);
    a = NULL;
}

void main()
{
    on_exit = on_exit_event;

    on_enter = test_grow;
    on_space = test_remove;
    on_tab = test_clear_all;
    on_e = test_enumerate;

    fps_max = 60;
    warn_level = 6;
    random_seed(0);

    while (!key_esc)
    {
        if (a)
        {
            DEBUG_VAR(a->capacity, 0);
            DEBUG_VAR(array_get_count(a), 20);
            DEBUG_VAR(is_array_not_empty(a), 40);

            // don't allow to crash when empty
            if (is_array_not_empty(a) == true)
            {
                var last = array_get_last(var, a);
                DEBUG_VAR(last, 80);

                int i = 0;
                for (i = 0; i < array_get_count(a); i++)
                {
                    var num = array_get_element_at(var, a, i);
                    DEBUG_VAR(num, 120 + 20 * i);
                }
            }
        }
        wait(1);
    }
}