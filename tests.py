import socket

address = 2130706433

address = address.to_bytes(4, 'big')
cmd = b"B"
data = b"GreatData!"
datalen = len(data).to_bytes(2, 'big')
packet = address+cmd+datalen + data


def soc(packet):
    s = socket.socket()
    s.connect(("127.0.0.1", 2500))
    s.send(packet)
    print(s.recv(1024))
    s.close()
