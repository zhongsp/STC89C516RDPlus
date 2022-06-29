# README

.hex file: https://developer.arm.com/documentation/ka003292/latest

```
# main fn
:0A 000F 00 C2A0C2A2C2A4C2A680FED5

# LJMP 0003
:03 0000 00 020003 F8

# prepare to call main
:0C 0003 00 787FE4F6D8FD75810702000F 3D

:00 0000 01 FF # End of file record

:（数据长度 - 2）（地址 - 4）（类型）(数据)(校验合)
```

```
:llaaaatt[dd...]cc
Each group of letters corresponds to a different field, and each letter represents a single hexadecimal digit. Each field is composed of at least two hexadecimal digits-which make up a byte-as described below:

: is the colon that starts every Intel HEX record.
ll is the record-length field that represents the number of data bytes (dd) in the record.
aaaa is the address field that represents the starting address for subsequent data in the record.
tt is the field that represents the HEX record type, which may be one of the following:
00 - data record
01 - end-of-file record
02 - extended segment address record
04 - extended linear address record
05 - start linear address record (MDK-ARM only)
dd is a data field that represents one byte of data. A record may have multiple data bytes. The number of data bytes in the record must match the number specified by the ll field.
cc is the checksum field that represents the checksum of the record. The checksum is calculated by summing the values of all hexadecimal digit pairs in the record modulo 256 and taking the two's complement.
```
