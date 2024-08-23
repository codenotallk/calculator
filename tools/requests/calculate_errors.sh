#!/bin/bash
curl -X GET 'http://localhost:1234/v1/calculate?type=subb&value_1=10&value_2=5'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?type=subb&value_1=a&value_2=5'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?type=subb&value_2=5'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?type=subb&value_1=10&value_2=b'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?type=subb&value_1=10'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?type=log&value_1=10&value_2=5'
echo
sleep 1

curl -X GET 'http://localhost:1234/v1/calculate?value_1=10&value_2=5'
echo
sleep 1