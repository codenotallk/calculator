#!/bin/bash

# curl http://localhost:1234/v1/report
# echo 
# sleep 1
# curl http://localhost:1234/v1/report?offset=1
# echo 
# sleep 1
# curl http://localhost:1234/v1/report?offset=a
# echo 
# sleep 1
# curl 'http://localhost:1234/v1/report?offset=0&from=2308/2024+10:50:00'
# echo 
# sleep 1
# curl 'http://localhost:1234/v1/report?offset=0&from=23/08/2024+11:05:00'
# echo 
# sleep 1
# curl 'http://localhost:1234/v1/report?offset=0&to=23/08/2024+10:55:00'
# echo 
# sleep 1
# curl 'http://localhost:1234/v1/report?offset=0&to=23/08/2024+1055:00'
# echo 
# sleep 1
curl 'http://localhost:1234/v1/report?offset=0&from=23/08/2024+10:53:00&to=23/08/2024+11:00:00'
echo 
sleep 1


