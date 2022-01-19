
#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <stdio.h>

/**
 * \file    dynamic_array.h
 * \brief   Dynamically growing array implementation.
 * 
 * \authors Originally created by Sidney Just aka JustSid
 *          Migrated to LiteC by Magomet Kocharov aka 3RUN
 * \date    15.01.2022
 *
 * dynamic_array.h provides a generic dynamically growing array
 */

/**
 * If uncommented - enables 'error' messages when something goes wrong.
 */
#define DEBUG_ARRAY

/**
 * Default initial capacity of the array. Array capacity set to this value automatically if <= 0 capacity was passed in array_create.
 */
#define ARRAY_INITIAL_CAPACITY 2

/**
 * A generic array which allows you handling a collection of any data type.
 * Since it doesn't have a fixed size, you can just add or remove elements.
 */
typedef struct array_t
{
    /**
	 * Size of the array.
	 */
    size_t capacity;

    /**
	 * Amount of stored elements in the array.
	 */
    size_t count;

    /**
	 * sizeof() of the stored data type.
	 */
    size_t type_size;

    /**
	 * The data stored in the array.
	 */
    void *data;
} array_t;

/**
 * Creates a new array with the given parameters and returns it's pointer to the array_create macros.
 * \param   type_size       The sizeof of the elements array is going to collect.
 * \param   capacity        Initial capacity of the array.
 * \return				    Pointer to a new array, or NULL if failed.
 */
array_t *_array_create(size_t type_size, size_t capacity);

/**
 * Destroys the array.
 * \param   array           The array to be destroyed.
 */
void array_destroy(array_t *array);

/**
 * Changes the capacity of the array to the given new_capacity.
 * \param   array           The array to change it's capacity.
 * \param   new_capacity    The new capacity to change array's capacity to.
 */
void array_change_size_to(array_t *array, size_t new_capacity);

/**
 * Returns amount of stored elements from the given array.
 * \param   array           The array to return it's elements count.
 * \return				    Amount of stored elements in the array, or -1 if failed.
 */
size_t array_get_count(array_t *array);

/**
 * Checks whether given array is empty or not. 
 * \param   array           The array to check.
 * \return				    TRUE - if not empty, otherwise (even if failed) - FALSE.
 */
int is_array_not_empty(array_t *array);

/**
 * Returns the last element from the array and assigns it to the given value in the array_add macros.
 * \param   array           The array to get last element from.
 * \param   type_size       The sizeof of the element to be returned.
 * \return				    The last element from the given array, or NULL if failed.
 */
void *_array_add(array_t *array, size_t type_size);

/**
 * Returns the last element from the array and assigns it to NULL in the array_remove_last macros.
 * \param   array           The array to get last element from.
 * \return				    The last element from the given array, or NULL if failed.
 */
void *_array_remove_last(array_t *array);

/**
 * Returns the last element from the array and casts it to the given type in the array_get_last macros.
 * \param   array           The array to get last element from.
 * \param   type_size       The sizeof of the element to be returned.
 * \return				    The last element from the given array, or NULL if failed.
 */
void *_array_get_last(array_t *array, size_t type_size);

/**
 * Returns the element of the given array at the given index and casts it to the given type in the array_get_element_at macros.
 * \param   array           The array to get last element from.
 * \param   index           The index of the element in the array.
 * \param   type_size       The sizeof of the element to be returned.
 * \return				    The last element from the given array, or NULL if failed.
 */
void *_array_get_element_at(array_t *array, size_t index, size_t type_size);

/**
 * Creates new array.
 * \param   t           A data type that array is going to collect (f.e. var, int, float, ENTITY*).
 * \param   c           Initial capacity of the array (default value is defined by ARRAY_INITIAL_CAPACITY).
 * \return				Pointer to the created array, or NULL if failed.
 */
#define array_create(t, c) _array_create(sizeof(t), c)

/**
 * Adds new element at the end of the given array.
 * \param   t           A data type that array is going to collect (f.e. var, int, float, ENTITY*).
 * \param   a           Pointer to the array we are adding element to.
 */
#define array_add(t, a, v) *((t *)_array_add(a, sizeof(t))) = (v)

/**
 * Removes element from the end of the given array.
 * \param   t           A data type that array has previously collected (f.e. var, int, float, ENTITY*).
 * \param   a           Pointer to the array we are removing element from.
 */
#define array_remove_last(t, a) *((t *)_array_remove_last(a)) = NULL

/**
 * Removes all elements from the given array.
 * \param   a           Pointer to the array we are removing all elements from.
 */
#define array_clear(a) do { int i, count = a->count; for(i = 0; i < count; i ++) array_remove_last(var, a); }while(0)

/**
 * Returns the last element from the array. The element will be casted to the given data type.
 * \param   t           A data type to cast element to (f.e. var, int, float, ENTITY*).
 * \param   a           Pointer to the array we are getting element from.
 * \return				Array element casted to the data type given in t parameter above.
 */
#define array_get_last(t, a) *((t *)_array_get_last(a, sizeof(t)))

/**
 * Returns the element from the array at the given index. The element will be casted to the given data type.
 * \param   t           A data type to cast element to (f.e. var, int, float, ENTITY*).
 * \param   a           Pointer to the array we are getting element from.
 * \param   i           Index of the element in the array.
 * \return				Array element casted to the data type given in t parameter above.
 */
#define array_get_element_at(t, a, i) *((t *)_array_get_element_at(a, i, sizeof(t)))

/**
 * Begins enumerating through the array + 'v' is set to the next element of the array. Make sure to not use ';' at the end when using !
 * \param   t           A data type to cast element to (f.e. var, int, float, ENTITY*).
 * \param   a           Pointer to the array we are getting element from.
 * \param   v           Next element of the array + it's casted to the data type given above.
 */
#define array_enumerate_begin(t, a, v) do { int i; for(i = 0; i < a->count; i ++) { t v = array_get_element_at(t, a, i);

/**
 * Ends the enumerating through the array.
 * \param   a           Pointer to the array we are getting element from.
 */
#define array_enumerate_end(a) } } while(0)

#include "dynamic_array.c"
#endif