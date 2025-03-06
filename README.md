# access_all_threads_example

A simple Linux kernel module that demonstrates how to access and display information for all kernel threads. The module iterates through the thread list and prints each thread's address, PID, and name to the kernel log. You can control the maximum number of threads printed using the module parameter `mp_max_threads` (set to `0` for no limit).

## Building

1. Ensure you have the necessary build tools and kernel headers installed:
   ```bash
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```
2. Build the module by running:
   ```bash
   make
   ```

## Usage

- **Load the module** (optionally specifying the maximum number of threads to print):
  ```bash
  sudo insmod access_all_threads.ko mp_max_threads=0
  ```
  
- **Spawn some threads** The spawn_threads.py script spawns multiple threads using Python:
  ```bash
  python3 spawn_threads.py
  ```  
  
- **View kernel logs** to see the thread information:
  ```bash
  dmesg | tail
  ```
  
- **Unload the module**:
  ```bash
  sudo rmmod access_all_threads
  ```
  
- **Check kernel logs again** for module removal messages:
  ```bash
  dmesg | tail
  ```

Using the module with mp_max_threads=1 is quite interesting—it then displays only the thread currently running on the CPU. It is surprising to observe that in Linux, the thread executes the LKM code directly, without any intermediary daemon process.

## License

Dual MIT/GPL
