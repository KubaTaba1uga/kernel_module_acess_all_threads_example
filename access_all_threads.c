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
static void show_all_subthreads(struct task_struct *current_thread);

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
  int i = 0;

  // `get_current` fetches currently processed thread.
  first_thread = current_thread = get_current();

  if (max == 0) {
    max = INT_MAX;
  }

  while (i++ < max) {
    pr_info("Name=%s, "
            "Address=%p, "
            "Pid=%d, "
            "Tgid=%d,  "
            "\n",
            current_thread->comm, current_thread, current_thread->pid,
            current_thread->tgid);

    show_all_subthreads(current_thread);

    current_thread = next_task(current_thread);

    if (current_thread == first_thread) {
      break;
    }

    pr_info(
        "------------------------------------------------------------------\n");
  }

  pr_info("All threads amount: %d\n\n\n", i - 1);
};

static void show_all_subthreads(struct task_struct *current_thread) {
  struct task_struct *subthread;
  int i = 0;

  // In kernel every scheduable computin unit is a thread.
  // However there are few types of threads. When you are
  // forking your process then you are creating subprocess
  // with it's own PID nad TGID.
  pr_info("Forked threads (aka subprocesses):\n");

  list_for_each_entry(subthread, &current_thread->children, sibling) {
    i++;
    pr_info("Name=%s, "
            "Address=%p, "
            "Pid=%d, "
            "Tgid=%d,  "
            "\n",
            subthread->comm, subthread, subthread->pid, subthread->tgid);
  }

  pr_info("All forked threads amount: %d\n", i);
  i = 0;

  // When you are cloning your process then you are
  // creating subthread (look on spawn_threads.py for more
  // info). Cubthread has it's own PID but it shares TGID
  // with it's parent.
  pr_info("Cloned threads (aka subthreads):\n");

  list_for_each_entry(subthread, &current_thread->thread_group, thread_group) {
    i++;
    pr_info("Name=%s, "
            "Address=%p, "
            "Pid=%d, "
            "Tgid=%d,  "
            "\n",
            subthread->comm, subthread, subthread->pid, subthread->tgid);
  }

  pr_info("All cloned threads amount: %d\n", i);
}

module_param(mp_max_threads, int, 0);
MODULE_PARM_DESC(
    mp_max_threads,
    "Maximum amount of threads to print, 0 means no limit [0-infinity]");
module_init(access_all_threads_init);
module_exit(access_all_threads_exit);
