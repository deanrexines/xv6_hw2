#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Halt (shutdown) the system by sending a special
// signal to QEMU.
// Based on: http://pdos.csail.mit.edu/6.828/2012/homework/xv6-syscall.html
// and: https://github.com/t3rm1n4l/pintos/blob/master/devices/shutdown.c
int
sys_halt(void)
{
  char *p = "Shutdown";
  for( ; *p; p++)
    outw(0xB004, 0x2000);
  return 0;
}

int 
sys_clone(void)
  {
    uint *(*func_add) (void *);
    uint *arg_add;
    uint *stack_add;
 
   if(argint(0, (int*)&func_add) < 0)
     return -1;
   if(argint(1, (int*)&arg_add) < 0)
     return -1;
   if(argint(2, (int*)&stack_add) < 0)
     return -1;

   return clone(func_add, arg_add, stack_add);
 }

 int
 sys_join(void)
 {
    uint pid;
    void **stack_add;
    void **retval;
   if(argint(0, (int*)&pid) < 0)
      return -1;
   if(argint(1, (int*)&stack_add) < 0)
      return -1;
   if(argint(2, (int*)&retval) < 0)
      return -1;

    join(pid, stack_add, retval);
    return 0;
 }

 int
 sys_texit(void)
 {

    void *retval;
   if(argint(0, (int*)&retval) < 0)
      return -1;

  texit(retval);    
  return 0;
 } 

// Returns a mutex id
int sys_mutex_init(void) {
    return mutex_init();
}

int sys_mutex_destroy(void) {
    int id;
    if (argint(0, &id) < 0) {
        cprintf("sys_mutex_destroy argument error\n");
        return -1;
    }
    return mutex_destroy(id);
}

// acquire a created mutex lock
int sys_mutex_lock(void) {
    int id;
    if (argint(0, &id) < 0) {
        cprintf("sys_mutex_lock argument error\n");
        return -1;
    }
    return mutex_lock(id);
}

// unlock a locked mutex lock
int sys_mutex_unlock(void) {
    int id;
    if (argint(0, &id) < 0) {
        cprintf("sys_mutex_unlock argument error\n");
        return -1;
    }
    return mutex_unlock(id);
}
