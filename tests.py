import socket

address = b"10.50.5.74"
address = address + bytes(15-len(address))
cmd = b"DATA"
cmd = cmd+bytes(6-len(cmd))
data = b"Goodsmall"
packet = address+cmd+data

def soc(packet):
    s = socket.socket()
    s.connect(("127.0.0.1",2500))
    s.send(packet)
    print(s.recv(1024))
    s.close()