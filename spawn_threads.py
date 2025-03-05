import threading


def worker(thread_id):
    print(f"Worker {thread_id} started")
    while True:
        pass


threads = []

for i in range(5):
    t = threading.Thread(target=worker, args=(i,))
    t.start()
    threads.append(t)

# Optionally, wait for all threads to finish
for t in threads:
    t.join()
