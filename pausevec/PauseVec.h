#ifndef PAUSEVEC_H
#define PAUSEVEC_H

#include <stdexcept>

class PauseVec {
public:
    PauseVec();
    ~PauseVec();
    size_t capacity() const;
    size_t count() const;
    void push(int value);
    int lookup(size_t index);
    void mutate(size_t index, int value);
    int remove(size_t index);
    void remove_val(int value);

    static PauseVec create_pausevec();

private:
    int* size;  
    size_t size_capacity;  
    size_t count_elements;
    size_t last_resize_index;

    void resize(size_t new_size);
    void compact();
};

#endif
