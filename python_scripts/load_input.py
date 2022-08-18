import serial, struct
import time
write = serial.Serial(
    port='/dev/cu.usbmodem141102',
    baudrate=115200,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)
write.close()
write.open()
data=0xff
data_bytes= (data.to_bytes(2,'big',signed=True))
time.sleep(1)
write.write(data_bytes)




# READ FUNZIONA; SCEGLI LA SIZE IN READ E BONA. READ ASPETTA FINCHE NON LEGGE SIZE CARATTERI
# read = serial.Serial()
# read.baudrate = 115200
# read.port = '/dev/cu.usbmodem141102'
# read.open()
# var = read.read(size=8)
# print(var)
