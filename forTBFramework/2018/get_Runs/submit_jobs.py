#!venv/bin/python
import subprocess
import sys
import time
from crypt import decrypt as dcrypt
key="455f2d9a7e15d5220ba0519b0e11c2b5f905d6e8ebf66f2503b25f6ae652bbed478e1466c6388099f79c5a1c56727e64509dd1cae9d95456fefc224e35411297e419f2b8cf5b097ceba6bbf022cdebe58f63880e795df1852702caf89d4a13df68684646c9b172ee9af75d98f605f9d1fa8f627641e7e61270acfcecc8f81064e97bfcc9730fbcd8ffcafaf3a883d0d0ba7ebfd8c7d26d97f23010542090582117b895d338f1dce9aab794317dc7ed622cc92865160b11670adb333ad42d0ebdd8927e2e3a0aa8a4fb5abc28e1fba45a59feed2a1ac565f7ee0b326723b80047843db15f283ba94e417edda1acb85b32baf24a2180e991874a1b12b9caf236f3"
passwd = dcrypt(key)
print passwd



ssh = subprocess.Popen(["ssh","cern"],
                       shell=False,
                       stdin=subprocess.PIPE,
                       stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE)

time.sleep(10)
ssh.communicate(input=passwd)[0]

result = ssh.stdout.readlines()
if result == []:
    error = ssh.stderr.readlines()
    print >>sys.stderr, "ERROR: %s" % error
else:
    print result
