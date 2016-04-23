#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "pthread.h"

// Implement your pthreads library here.

<<<<<<< HEAD
 int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void * (*start_routine) (void *), void *arg) {
    void *stack = malloc(4096);
    thread->pid = clone(start_routine, arg, stack);
    if (thread->pid < 0) {
        free(stack);
        return -1;
    }
    return thread->pid;
}
 
int pthread_join(pthread_t thread, void **retval) {
    void *stack = 0;
    int status = join(thread.pid, &stack, retval);
    if (stack) {
        free(stack);
    }
    return status;
}

int pthread_exit(void *retval) {
    texit(retval);
    return 0;
}


int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {
    mutex->id = mutex_init();
    if (mutex->id < 0) {
        return -1;
    }
    return 0;
}
int pthread_mutex_destroy(pthread_mutex_t *mutex) {
    return mutex_destroy(mutex->id);
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
    return mutex_lock(mutex->id);
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    return mutex_unlock(mutex->id);
}
=======
>>>>>>> b04c5f7e1c59edb4a25bffb7228e601f6651b0b6
