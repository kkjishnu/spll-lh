import math

ENERGY_ELECTRIC = 0.05

def energy_amplifier(d,d_naught):
    if (d<=d_naught):
        ret = e_fs*d*d
        return ret
    elif (d>d_naught):
        ret = e_mp*d*d*d*d
        return ret

def energy_transmit(k,d):
    ret = k*(ENERGY_ELECTRIC+(energy_amplifier(d,)*d*d))
    return ret

def energy_receive(k):
    ret = k*(ENERGY_ELECTRIC)