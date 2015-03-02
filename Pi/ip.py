import requests
import socket
import credentials
#import atexit, pexpect, pickle, socket, time, subprocess
#my_IP = socket.gethostbyname(socket.getfqdn())
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 0))
my_IP = '\n' + s.getsockname()[0]
hostname = socket.gethostname()
intro = hostname + "@"
status = "\nStatus:Online\n"
update = intro + my_IP + status
post_data = {'access_token':credentials.access_token, 'args':update}
post_response = requests.post(url=credentials.deviceURL, data=post_data)
print post_response
