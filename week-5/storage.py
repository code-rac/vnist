import os

def save_file(res, filename):	
	data_path = 'G:/chohai/vnist/week-5/data/'
	filename = data_path + filename
	if not os.path.exists(os.path.dirname(filename)):
		try:
			os.mkdir(os.path.dirname(filename))
		except OSError as exc:
			if exc.errno != errno.EEXIST:
				raise
	with open(filename, 'ab') as f:
		for packet in res:
			f.write(packet)


