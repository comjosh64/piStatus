import requests
import credentials

post_data = {'access_token':credentials.access_token, 'args':'CLEAR'}
post_response = requests.post(url=credentials.deviceURL, data=post_data)
print post_response
