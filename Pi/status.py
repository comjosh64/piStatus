from __future__ import division
from subprocess import PIPE, Popen
import requests
import socket
import datetime
import psutil
import credentials
import time
time.sleep(5)

def get_cpu_temperature():
    process = Popen(['vcgencmd', 'measure_temp'], stdout=PIPE)
    output, _error = process.communicate()
    return float(output[output.index('=') + 1:output.rindex("'")])

cpu_temperature = get_cpu_temperature()
cpu_usage = psutil.cpu_percent()
#print 'CPU Temp: ' +  str(cpu_temperature)
#print 'CPU: ' + str(cpu_usage) + "%"

#print 'RAM: ' + str(ram_percent_used) + "%"
disk = psutil.disk_usage('/')
disk_percent_used = disk.percent
#print 'Disk: ' + str(disk_percent_used) + "%"
system = 'CPU: ' + str(cpu_temperature) + 'C ' + str(cpu_usage) + "%\nDisk:" + str(disk_percent_used) + "%\n \n"  
#print '_______'
print system

timestamp = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d %H:%M:%S')
timestamp = timestamp + "\n"
#import atexit, pexpect, pickle, socket, time, subprocess
#my_IP = socket.gethostbyname(socket.getfqdn())
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(('8.8.8.8', 0))
my_IP = '\n' + s.getsockname()[0]
hostname = socket.gethostname()
intro = hostname + "@"
status = "\nStatus:Online"
update = timestamp + intro + my_IP + status

post_data = {'access_token':credentials.access_token, 'args':system}
post_response = requests.post(url=credentials.deviceURL, data=post_data)
print post_response

post_data = {'access_token':credentials.access_token, 'args':update}
post_response = requests.post(url=credentials.deviceURL, data=post_data)
print post_response



