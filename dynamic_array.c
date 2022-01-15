
array_t *_array_create(size_t type_size, size_t capacity)
{
    if (capacity <= 0)
    {
        capacity = ARRAY_INITIAL_CAPACITY;
    }

    array_t *array = sys_malloc(sizeof(array_t));
    if (!array)
    {
        return NULL;
    }

    array->capacity = capacity;
    array->count = 0;
    array->type_size = type_size;
    array->data = sys_malloc(capacity * type_size);

    if (!array->data)
    {
        return NULL;
    }

    return array;
}

void array_destroy(array_t *array)
{
    if (!array)
    {
        diag("ERROR in array_destroy! Array pointer is NULL!");
        return;
    }

    sys_free(array->data);
    array->data = NULL;
    sys_free(array);
}

void array_change_size_to(array_t *array, size_t new_capacity)
{
    if (!array)
    {
        diag("ERROR in array_change_size_to! Array pointer is NULL!");
        return;
    }

    if (new_capacity == 0) // if something goes wrong, double the capacity
    {
        new_capacity = array->capacity * 2;
    }

    void *new_data = sys_malloc(new_capacity * array->type_size);
    memcpy(new_data, array->data, array->count * array->type_size);
    sys_free(array->data);

    array->data = new_data;
    array->capacity = new_capacity;
}

size_t array_get_count(array_t *array)
{
    if (!array)
    {
        diag("ERROR in array_get_count! Array pointer is NULL!");
        return -1;
    }

    return array->count;
}

int is_array_not_empty(array_t *array)
{
    if (!array)
    {
        diag("ERROR in is_array_not_empty! Array pointer is NULL!");
        return false;
    }

    return array->count > 0;
}

void *_array_add(array_t *array, size_t type_size)
{
    if (!array)
    {
        diag("ERROR in _array_add! Array pointer is NULL!");
        return NULL;
    }

    if (type_size != array->type_size)
    {
#ifdef DEBUG_ARRAY
        error("Array type size mismatch");
#endif
        diag("ERROR in _array_add! Array type size mismatch");
        return NULL;
    }

    if (array->count >= array->capacity)
    {
        array_change_size_to(array, array->capacity * 2);
    }

    void *last_element = (unsigned char *)(array->data) + array->count * type_size;
    array->count++;

    return last_element;
}

void *_array_remove_last(array_t *array)
{
    if (!array)
    {
        diag("ERROR in _array_remove_last! Array pointer is NULL!");
        return NULL;
    }

    array->count--;
    if (array->count < (array->capacity * 0.5))
    {
        array_change_size_to(array, array->capacity * 0.5);
    }

    void *last_element = (unsigned char *)(array->data) + array->count * array->type_size;
    return last_element;
}

void *_array_get_last(array_t *array, size_t type_size)
{
    if (!array)
    {
        diag("ERROR in _array_get_last! Array pointer is NULL!");
        return NULL;
    }

    if (type_size != array->type_size)
    {
#ifdef DEBUG_ARRAY
        error("Array type size mismatch");
#endif
        diag("ERROR in _array_get_last! Array type size mismatch");
        return NULL;
    }

    if (is_array_not_empty(array) != true)
    {
        diag("ERROR in _array_get_last! Array is empty!");
        return NULL;
    }

    size_t index = array->count - 1;
    return (void *)((unsigned char *)(array->data) + index * type_size);
}

void *_array_get_element_at(array_t *array, size_t index, size_t type_size)
{
    if (!array)
    {
        diag("ERROR in _array_get_element_at! Array pointer is NULL!");
        return NULL;
    }

    if (index < 0 || index >= array->count)
    {
#ifdef DEBUG_ARRAY
        error("Array out of bounds access");
#endif
        diag("ERROR in _array_get_element_at! Array out of bounds access");
        return NULL;
    }

    if (type_size != array->type_size)
    {
#ifdef DEBUG_ARRAY
        error("Array type size mismatch");
#endif
        diag("ERROR in _array_get_element_at! Array type size mismatch");
        return NULL;
    }

    if (is_array_not_empty(array) != true)
    {
        diag("ERROR in _array_get_element_at! Array is empty!");
        return NULL;
    }

    return (void *)((unsigned char *)(array->data) + index * type_size);
}