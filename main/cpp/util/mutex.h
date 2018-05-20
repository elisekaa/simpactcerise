#pragma once

#include <omp.h>

class Mutex
{
public:
        ///
        explicit Mutex() { omp_init_lock(&m_lock); }

        ///
        ~Mutex() { omp_destroy_lock(&m_lock); }

        ///
        void lock() { omp_set_lock(&m_lock); }

        ///
        void unlock() { omp_unset_lock(&m_lock); }

private:
        omp_lock_t m_lock;
};
