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
#include <linux/limits.h>
#include <linux/module.h>
#include <linux/preempt.h>
#include <linux/sched.h>

MODULE_AUTHOR("KubaTaba1uga");
MODULE_DESCRIPTION("a simple LKM showing all threads");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int mp_max_threads;
static void show_all_threads(int);

static int __init access_all_threads_init(void) {
  pr_info("Inserted\n");

  // We need to ensure that we are in task ctx because we're gonna
  //   block cpu with our while loop.
  if (!in_task()) {
    pr_warn("Unable to execute in interrupt ctx\n");
    return 1;
  }

  show_all_threads(mp_max_threads);

  return 0;
}

static void __exit access_all_threads_exit(void) {
  pr_info("Removed\n");

  if (!in_task()) {
    pr_warn("Unable to execute in interrupt ctx\n");
    return;
  }

  show_all_threads(mp_max_threads);
}

static void show_all_threads(int max) {
  // `struct task_struct` holds thread data.
  struct task_struct *current_thread, *first_thread;

  // `get_current` fetches currently processed thread.
  first_thread = current_thread = get_current();

  if (max == 0) {
    max = INT_MAX;
  }

  while (max-- > 0) {
    pr_info("Address=%p, "
            "Pid=%d, "
            "Name=%s, "
            "\n",
            current_thread, current_thread->pid, current_thread->comm);

    current_thread = next_task(current_thread);

    if (current_thread == first_thread) {
      pr_info("Stoping iteration\n\n\n");
      break;
    }
  }
};

module_param(mp_max_threads, int, 0);
MODULE_PARM_DESC(
    mp_max_threads,
    "Maximum amount of threads to print, 0 means no limit [0-infinity]");
module_init(access_all_threads_init);
module_exit(access_all_threads_exit);
