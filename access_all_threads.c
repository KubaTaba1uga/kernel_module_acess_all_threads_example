/*
 * access_all_threads.c
 ****************************************************************
 * Brief Description:
 * A very simple module which shows how one can access all kernel threads from
 *  within linux kernel.
 */

#include "linux/printk.h"
#include "linux/sched/signal.h"
#include <asm/current.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_AUTHOR("KubaTaba1uga");
MODULE_DESCRIPTION("a simple LKM showing all threads");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init access_all_threads_init(void) {
  pr_info("Inserted\n");

  // `struct task_struct` holds thread data.
  struct task_struct *current_thread, *first_thread;

  first_thread = current_thread = get_current();

  while (true) {
    pr_info("Thread address=%p, thread_pid=%d\n", current_thread,
            current_thread->pid);

    current_thread = next_task(current_thread);

    if (current_thread == first_thread) {
      pr_info("Stoping iteration\n\n\n");

      break;
    }
  }

  return 0;
}

static void __exit access_all_threads_exit(void) { pr_info("Removed\n"); }

module_init(access_all_threads_init);
module_exit(access_all_threads_exit);
