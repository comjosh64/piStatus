import requests
import socket
#import atexit, pexpect, pickle, socket, time, subprocess
#my_IP = socket.gethostbyname(socket.getfqdn())
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 0))
my_IP = '\n' + s.getsockname()[0]
hostname = socket.gethostname()
intro = hostname + "@"
status = "\nStatus:Online\n"
update = intro + my_IP + status
post_data = {'access_token':'d5f512ede31ddf74510d043a6bb9afe57952cad8', 'args':update}
post_response = requests.post(url='https://api.spark.io/v1/devices/54ff72066678574947220367/prntscr', data=post_data)
print post_response
