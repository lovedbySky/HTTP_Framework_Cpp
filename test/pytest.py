import requests
import json, base64


# for i in range(3):
#     requests.get("http://localhost:9090/index")


requests.post("http://localhost:9090/login", base64.encodebytes(b"username=admin&password=1234567"))

# for i in range(3):
#     requests.put("http://localhost:8080/index")
    