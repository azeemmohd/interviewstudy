#ifndef DEQUE_H_
#define DEQUE_H_

#include "common.h"

/**
 * A dynamic array that supports amortized constant time insertion and removal
 * at both ends and constant time access.
 */
typedef struct deque_s Deque;

/**
 * Deque configuration object. Used to initialize a new Deque with specific
 * values.
 */
typedef struct deque_conf_s {
    /**
     * The initial capacity of the deque. Must be a power of two.
     * if a non power of two is passed, it will be rounded to the
     * closest upper power of two */
    size_t capacity;

    /**
     * Memory allocators used to allocate the Vector structure and the
     * underlying data buffers. */
    void *(*mem_alloc)  (size_t size);
    void *(*mem_calloc) (size_t blocks, size_t size);
    void  (*mem_free)   (void *block);
} DequeConf;

/**
 * Deque iterator object. Used to iterate over the elements of a deque
 * in an ascending order. The iterator also supports operations for safely
 * removing and adding elements during iteration.
 *
 * @code
 * DequeIter i;
 * deque_iter_init(&i);
 *
 * while (deque_iter_has_next(&i)) {
 *     MyType *e = deque_iter_next(&i);
 * }
 * @endcode
 */
typedef struct deque_iter_s {
    /**
     * The deque associated with this iterator.*/
    Deque *deque;

    /**
     * The current logical position of the iterator. */
    size_t index;
} DequeIter;

Deque*     deque_new             (void);
Deque*     deque_new_conf        (DequeConf *conf);
void       deque_conf_init       (DequeConf *conf);

void       deque_destroy         (Deque *deque);
void       deque_destroy_free    (Deque *deque);

bool       deque_add             (Deque *deque, void *element);
bool       deque_add_first       (Deque *deque, void *element);
bool       deque_add_last        (Deque *deque, void *element);
bool       deque_add_at          (Deque *deque, void *element, size_t index);
void*      deque_replace_at      (Deque *deque, void *element, size_t index);

void*      deque_remove          (Deque *deque, void *element);
void*      deque_remove_at       (Deque *deque, size_t index);
void*      deque_remove_first    (Deque *deque);
void*      deque_remove_last     (Deque *deque);
void       deque_remove_all      (Deque *deque);
void       deque_remove_all_free (Deque *deque);

void*      deque_get             (Deque *deque, size_t index);
void*      deque_get_first       (Deque *deque);
void*      deque_get_last        (Deque *deque);

Deque*     deque_copy_shallow    (Deque *deque);
Deque*     deque_copy_deep       (Deque *deque, void *(*cp) (void*));

void       deque_reverse         (Deque *deque);
bool       deque_trim_capacity   (Deque *deque);

size_t     deque_contains        (Deque *deque, void *element);
size_t     deque_size            (Deque *deque);
size_t     deque_capacity        (Deque *deque);

size_t     deque_index_of        (Deque *deque, void *element);

void       deque_foreach         (Deque *deque, void (*op) (void *));

void       deque_iter_init       (DequeIter *iter, Deque *deque);
bool       deque_iter_has_next   (DequeIter *iter);
void*      deque_iter_next       (DequeIter *iter);
void*      deque_iter_remove     (DequeIter *iter);
bool       deque_iter_add        (DequeIter *iter, void *element);
void*      deque_iter_replace    (DequeIter *iter, void *replacement);
size_t     deque_iter_index      (DequeIter *iter);

const void* const* deque_get_buffer(Deque *deque);

#endif /* DEQUE_H_ */
