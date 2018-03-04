# Testing time-based one-time password
# Requires python3
from dotenv import load_dotenv, find_dotenv
import os
import httplib2
import hmac
import hashlib
import struct
import json
import pyotp
import base64

#Load env variables
load_dotenv(find_dotenv())

root = os.getenv("DESTINATION_URL")
content_type = "application/json"
userid = os.getenv("USERID")
secret_suffix = os.getenv("SECRET")
shared_secret = userid+secret_suffix
secret_encode = base64.b32encode(str.encode(shared_secret))


totp = pyotp.TOTP(secret_encode)
totp.digits = 6
totp.digest = hashlib.sha512

# Can also declare the above in a single line as follows
# totp = pyotp.TOTP(secret_encode, digits=6, digest=hashlib.sha512)

passwd = totp.now()

data = {
    "content": "some content"
}

h = httplib2.Http()
h.add_credentials( userid, passwd )
header = {"content-type": "application/json"}
resp, content = h.request(root, "POST", headers = header, body = json.dumps(data))
print(resp)
