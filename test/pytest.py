import requests

for i in range(3):
    requests.get("http://localhost:8080/index.html")

for i in range(3):
    requests.post("http://localhost:8080/index.html")

for i in range(3):
    requests.put("http://localhost:8080/index.html")

for i in range(3):
    requests.put("http://localhost:8080/index")

for i in range(3):
    requests.put("http://localhost:8080/readme")
    