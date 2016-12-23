import Queue
import threading
import socket
import time

exitFlag = 0

class myThread(threading.Thread):
	def __init__(self, queue, sock, addr, lock=threading.Lock()):
		threading.Thread.__init__(self)
		self.sock = sock
		self.queue = queue
		self.lock = lock
		self.addr = addr

	def run(self):
		process_data(self.queue, self.sock, self.addr)

def process_data(queue, sock, addr):
	while not exitFlag:
		lock.acquire()
		if not queue.empty():
			data = queue.get()
			# print workQueue.qsize()
			sock.sendto(data, addr)
			lock.release()
		else:
			lock.release()


start_at = time.time()

lock = threading.Lock()
workQueue = Queue.Queue()
threads = []
host = '192.168.1.33'
port = 3636
addr = (host, port)

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# sock.connect((host, port))


# Create new threads
for i in range(5):
	thread = myThread(workQueue, sock, addr)
	thread.start()
	threads.append(thread)

# Fill the queue
print 'fill the queue'
lock.acquire()
file = open('test.wmv', 'rb')
seek = 0
count = 0
while True:
	file.seek(seek)
	data = file.read(32000)
	if not data:
		break
	workQueue.put(data)
	count+=1
	seek+=32000

print workQueue.qsize()
MAX_SIZE = count

sock.sendto(str(MAX_SIZE), addr)
time.sleep(1)
lock.release()

# Wait for queue to empty
while not workQueue.empty():
	pass

# Notify threads it's time to exit
exitFlag = 1

# Wait for all threads to complete
for t in threads:
	t.join()


print 'Exiting Main Thread in', time.time() - start_at
file.close()