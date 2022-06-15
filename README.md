# WAV-Loop
Wav file loop in SD card based on ZYNQ

ZYNQ.tcl is for configuration for ZYNQ based on PYNQ board (Compatible for ZYNQ mb need to change DDR configuration for different development board)

![image](https://user-images.githubusercontent.com/102744628/173849195-33751eac-f943-4202-8016-d227288dc01d.png)

Board Support Package setting:
 
![image](https://user-images.githubusercontent.com/102744628/173850154-5f8abcc2-8cd4-446b-b7ac-5fecdef338d8.png)

UART output below:

--------test--------
success to mount the default drive

fsize = 367ECE


ChunkID = RIFF

ChunkSize = 367EC6

Format = WAVE


Subchunk1ID = fmt 

Subchunk1Size = 16

AudioFormat = 1

NumChannels = 2

SampleRate = 44100

ByteRate = 176400

BlockAlign = 4

BitsPerSample = 16


blockID = data

blockSize = 367E00


RIFF chunk and fmt chunk writing:

pointer position = 2C; end or not:0 ; byte wrote = 2C

data chunk writing:

pointer position = 2F02C; end or not:0 ; byte wrote = 2F000

pointer position = 5E02C; end or not:0 ; byte wrote = 2F000

pointer position = 8D02C; end or not:0 ; byte wrote = 2F000

pointer position = BC02C; end or not:0 ; byte wrote = 2F000

pointer position = EB02C; end or not:0 ; byte wrote = 2F000

pointer position = 11A02C; end or not:0 ; byte wrote = 2F000

pointer position = 14902C; end or not:0 ; byte wrote = 2F000

pointer position = 17802C; end or not:0 ; byte wrote = 2F000

pointer position = 1A702C; end or not:0 ; byte wrote = 2F000

pointer position = 1D602C; end or not:0 ; byte wrote = 2F000

pointer position = 20502C; end or not:0 ; byte wrote = 2F000

pointer position = 23402C; end or not:0 ; byte wrote = 2F000

pointer position = 26302C; end or not:0 ; byte wrote = 2F000

pointer position = 29202C; end or not:0 ; byte wrote = 2F000

pointer position = 2C102C; end or not:0 ; byte wrote = 2F000

pointer position = 2F002C; end or not:0 ; byte wrote = 2F000

pointer position = 31F02C; end or not:0 ; byte wrote = 2F000

pointer position = 34E02C; end or not:0 ; byte wrote = 2F000

pointer position = 367ECE; end or not:1 ; byte wrote = 19EA2


new fsize = 367ECE

ChunkID = RIFF

ChunkSize = 367EC6

Format = WAVE


Subchunk1ID = fmt 

Subchunk1Size = 16

AudioFormat = 1

NumChannels = 2

SampleRate = 44100

ByteRate = 176400

BlockAlign = 4

BitsPerSample = 16


blockID = data

blockSize = 367E00


----done----
