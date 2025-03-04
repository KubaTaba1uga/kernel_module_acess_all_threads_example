# access+all+threads_example

A simple LKM that shows how one can access kernel or userspace threads. One thread is accessed we prints it's PID.

## Building

1. Install required tools and kernel headers:
   ```bash
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```
2. Build the module:
   ```bash
   make
   ```

## Usage

- Insert the module:
  ```bash
  sudo insmod mymodule.ko
  ```
- View kernel logs:
  ```bash
  dmesg | tail
  ```
- Remove the module:
  ```bash
  sudo rmmod mymodule
  ```

## License

Dual MIT/GPL
