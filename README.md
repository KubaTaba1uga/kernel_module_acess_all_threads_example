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

## License

Dual MIT/GPL
