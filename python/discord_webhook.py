#Testing Discord Webhook and loading variables from local environment
from dotenv import load_dotenv, find_dotenv
import os
import httplib2
import json

#Find and load environment variables from local .env file
load_dotenv(find_dotenv())

url = os.getenv("WEBHOOK_URL")
user = os.getenv("USERID")
avatar = os.getenv("AVATAR")
header = {"content-type": "application/json"}

# Sample object to send
data = {
    "username": user,
	"avatar_url": avatar,
    "content": "a"
}


h = httplib2.Http()
resp, content = h.request(url, "POST", headers = header, body = json.dumps(data))
