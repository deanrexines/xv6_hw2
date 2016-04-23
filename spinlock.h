// Mutual exclusion lock.
<<<<<<< HEAD
#ifndef SPINLOCK_H
#define SPINLOCK_H
=======
>>>>>>> b04c5f7e1c59edb4a25bffb7228e601f6651b0b6
struct spinlock {
  uint locked;       // Is the lock held?
  
  // For debugging:
  char *name;        // Name of lock.
  struct cpu *cpu;   // The cpu holding the lock.
  uint pcs[10];      // The call stack (an array of program counters)
                     // that locked the lock.
};

<<<<<<< HEAD
#endif
=======
>>>>>>> b04c5f7e1c59edb4a25bffb7228e601f6651b0b6
