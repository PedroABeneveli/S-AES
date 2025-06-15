from base64 import b64decode, b64encode
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import timeit

key = b'\xdc\xf7?u\x8b>.C\xdb\x9d\xb8D\x1c\x8b,\xd6'
msg = input().encode("utf-8")
nonce = b64decode("NgxlaIY3FkI=")
cipher = AES.new(key, AES.MODE_CTR, nonce=nonce)

t_init = timeit.default_timer()
cipher_text = cipher.encrypt(msg)
t_end = timeit.default_timer()

print("Tempo em ms para realizar a encriptacao da mensagem no Modo CTR: ", (t_end - t_init) * 1000, "ms")

print("Deseja visualizar o texto cifrado em base64? (y/n)")
ans = input()

if (ans == "y"):
    print(b64encode(cipher_text).decode('utf-8'))