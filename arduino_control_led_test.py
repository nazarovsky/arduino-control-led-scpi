# test SCPI commands for Arduino Control Led in Python 
import serial
import os,sys
from time import sleep 

#   Supported SCPI commands are here:
#      arduino_control_led_scpi/arduino_control_led_scpi.ino 
#

def query(sess,q):
    print('q> = {} | '.format(q.rstrip()), end = '')
    sess.write(bytes(q, 'utf-8'))
    sleep(0.01)
    r = sess.readline().decode('utf-8').rstrip()
    print('< = {}'.format(r))
    return r

def send(sess,q):
    print('s> = {} '.format(q.rstrip()))
    sess.write(bytes(q, 'utf-8'))
    return 

def main():
    sess = serial.Serial(port='COM4', baudrate=115200, timeout=0.1)    
    print('Wait for Arduino reset after opening Serial')
    sleep(4)    
    idn = query(sess,'*IDN?\n')
    sleep(1)    
    for i in range(11):
        for j in range(4):
            idn = send(sess,'LED{0:1d}:BRI {1:2d}\n'.format(j,i))        
            sleep(0.05)
    sleep(1)    
    idn = send(sess,'LED:TEST\n')
    sleep(1)    
    idn = send(sess,'LED:OFF\n')
    sleep(0.5)    
    idn = send(sess,'LED:ON\n')
    sleep(0.5)    
    idn = send(sess,'LED:OFF\n')
    sleep(0.5)    
    for i in range(11):
        idn = send(sess,'LED:BRI:INC\n')        
        sleep(0.03)
    idn = query(sess,'LED:BRI?\n')
    sleep(1)    
    for i in range(11):
        idn = send(sess,'LED:BRI:DEC\n')        
        sleep(0.03)
    idn = query(sess,'LED:BRI?\n')
    sleep(1)    
    sys.exit(1)

if __name__ == '__main__':
    main()    