
#ifndef DISABLEOPENMP

#include "mutex.h"
#include <iostream>
#include <stdlib.h>

Mutex::Mutex() { omp_init_lock(&m_lock); }

Mutex::~Mutex() { omp_destroy_lock(&m_lock); }

#endif // !DISABLEOPENMP
