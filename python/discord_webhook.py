#Testing Discord Webhook and loading variables from local environment
from dotenv import load_dotenv, find_dotenv
import os
import httplib2
import json

#Find and load environment variables from local .env file
load_dotenv(find_dotenv())

url = os.getenv("WEBHOOK_URL")
header = {"content-type": "application/json"}

# Sample object to send
data = {
    "username": "Test",
    "content": "Hello World!"
}


h = httplib2.Http()
resp, content = h.request(url, "POST", headers = header, body = json.dumps(data))
