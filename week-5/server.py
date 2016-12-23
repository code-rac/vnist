import socket
import threading
import time
import Queue

res = []
lock = threading.Lock()
exitFlag = 0

class myThread(threading.Thread):
	def __init__(self, sock, lock=threading.Lock()):
		threading.Thread.__init__(self)
		self.lock = lock
		self.sock = sock

	def run(self):
		process_data(self.sock)

def process_data(sock):
	sock.settimeout(0.2)
	while True:
		lock.acquire()
		try:
			data, addr = sock.recvfrom(40000)
			lock.release()
			res.append(data)
			print len(res)
		except:
			lock.release()
			break


host = '192.168.1.33'
port = 3636
addr = (host, port)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.sendto('test.wmv', addr)
threads = []
for i in range(30):
	t = myThread(sock)
	t.start()
	threads.append(t)

for t in threads:
	t.join()

print len(res)
