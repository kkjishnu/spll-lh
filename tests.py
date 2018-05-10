import socket

#address = 2130706433
#address = 168296452
address = 3232246638
address = address.to_bytes(4, 'big')
cmd = b"A"
data = b"GreatData!"
datalen = len(data).to_bytes(2, 'big')
packet = address+cmd+datalen + data

def get_routing_table():
    address = 2130706433
    address = address.to_bytes(4, 'big')
    cmd = b"C"
    data = b"Give me routing table!"
    datalen = len(data).to_bytes(2, 'big')
    packet = address+cmd+datalen + data
    s = socket.socket()
    s.connect(("127.0.0.1", 2500))
    s.send(packet)
    a = s.recv(1024)
    print(len(a))
    s.close()
    return a

def route_soc(address_list):
    address = 2130706433
    address = address.to_bytes(4, 'big')
    cmd = b"B"
    table_len = (int(len(address_list)/2)).to_bytes(2,'big')
    data = table_len
    for i in range(len(address_list)):
        address_list[i] = address_list[i].to_bytes(4,'big')
    for i in address_list:
        data += i
    print(len(data))
    datalen = len(data).to_bytes(2, 'big')
    packet = address+cmd+datalen+data
    print(packet)
    ret = soc(packet)
    return ret

def soc(packet):
    s = socket.socket()
    s.connect(("127.0.0.1", 2500))
    s.send(packet)
    a = s.recv(1024)
    print(len(a))
    s.close()
    return a
