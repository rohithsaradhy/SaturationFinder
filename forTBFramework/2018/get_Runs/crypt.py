#!venv/bin/python
from Crypto.PublicKey import RSA
from Crypto.Util import asn1
import sys
from base64 import b64decode
import binascii


Loc_PubKey = "/home/rsaradhy/.ssh/id_rsa.pub"
Loc_PriKey = "/home/rsaradhy/.ssh/id_rsa"

pubKey = open(Loc_PubKey).readline()
priKey = ""
for line in open(Loc_PriKey).readlines():
    priKey+=line



def encrypt(data_in): #outputs data in binary
    pubKeyObj =  RSA.importKey(pubKey)
    emsg = pubKeyObj.encrypt(data_in, 'x')[0]
    return bin2hex(emsg)
def decrypt(data_in):
    privKeyObj = RSA.importKey(priKey)
    dmsg = privKeyObj.decrypt(hex2bin(data_in))
    return dmsg



def bin2hex(binStr):
    return binascii.hexlify(binStr)

def hex2bin(hexStr):
    return binascii.unhexlify(hexStr)






#Generate Own Key
# key = RSA.generate(2048)
# binPrivKey = key.exportKey("DER")
# binPubKey =  key.publickey().exportKey("DER")
#

#using already generated pub pri pair
#








if __name__== "__main__":
    # print decrypt(encrypt("It Works"))
    # print encrypt("It Works")

    if len(sys.argv) > 2:
        Option = sys.argv[1]
        Message = sys.argv[2]
        if Option == "-e":
            print encrypt(Message)
        elif Option == "-d":
            print decrypt(Message)
