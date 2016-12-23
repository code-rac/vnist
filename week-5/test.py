import socket
import threading
import time
import Queue
import storage
###################################################################
res = []
lock = threading.Lock()
class threadRecv(threading.Thread):
	def __init__(self, sock, addr):
		threading.Thread.__init__(self)
		self.sock = sock
		self.addr = addr

	def run(self):
		process_recv(self.sock, self.addr)
def process_recv(sock, ADDR):
	sock.settimeout(0.2)
	while True:
		lock.acquire()
		try:
			data, addr = sock.recvfrom(40000)
			lock.release()
			if addr == ADDR:
				res.append(data)
		except:
			lock.release()
			break
			
def recv_data(sock, addr, size):
	threads = []
	for i in range(30):
		t = threadRecv(sock, addr)
		t.start()
		threads.append(t)
	for t in threads:
		t.join()
	if len(res) == int(size):
		# storage.save_file(res, 'testxemdckhong')
		return True
	return False
###################################################################
exitFlag = 0
class threadSend(threading.Thread):
	def __init__(self, queue, sock, addr, lock=threading.Lock()):
		threading.Thread.__init__(self)
		self.sock = sock
		self.queue = queue
		self.lock = lock
		self.addr = addr
	def run(self):
		process_send(self.queue, self.sock, self.addr)
def process_send(queue, sock, addr):
	while not exitFlag:
		lock.acquire()
		if not queue.empty():
			data = queue.get()
			sock.sendto(data, addr)
			lock.release()
		else:
			lock.release()

def send_data(sock, addr, file_path):
	global exitFlag
	workQueue = Queue.Queue()
	threads = []

	for i in range(5):
		thread = threadSend(workQueue, sock, addr)
		thread.start()
		threads.append(thread)

	lock.acquire()
	file = open(file_path, 'rb')
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

	file.close()
###################################################################

def main():
	host = '0.0.0.0'
	port = 3636

	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.bind((host, port))

	size, addr = sock.recvfrom(1024) 
	if recv_data(sock, addr, size):
		print 'Success!!'
	else:
		print 'Packet lost'	

if __name__ == '__main__':
	main()