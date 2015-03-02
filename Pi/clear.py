import requests

post_data = {'access_token':'d5f512ede31ddf74510d043a6bb9afe57952cad8', 'args':'CLEAR'}
post_response = requests.post(url='https://api.spark.io/v1/devices/54ff72066678574947220367/prntscr', data=post_data)
print post_response
