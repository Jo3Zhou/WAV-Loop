#include "xparameters.h"
#include "xil_exception.h"
#include "xscugic.h"
#include "ff.h"

typedef struct WAV_RIFF {
    /* chunk "riff" */
    char ChunkID[4];   /* "RIFF" */
    /* sub-chunk-size */
    u32 ChunkSize; /* 36 + Subchunk2Size */
    /* sub-chunk-data */
    char Format[4];    /* "WAVE" */
} RIFF_s;

typedef struct WAV_FMT {
    /* sub-chunk "fmt" */
    char Subchunk1ID[4];   /* "fmt " */
    /* sub-chunk-size */
    u32 Subchunk1Size; /* 16 for PCM */
    /* sub-chunk-data */
    u16 AudioFormat;   /* PCM = 1*/
    u16 NumChannels;   /* Mono = 1, Stereo = 2, etc. */
    u32 SampleRate;    /* 8000, 44100, etc. */
    u32 ByteRate;  /* = SampleRate * NumChannels * BitsPerSample/8 */
    u16 BlockAlign;    /* = NumChannels * BitsPerSample/8 */
    u16 BitsPerSample; /* 8bits, 16bits, etc. */
} FMT_s;

typedef struct WAV_DATA {
    /* sub-chunk "data" */
    char Subchunk2ID[4];   /* "data" */
    /* sub-chunk-size */
    uint32_t Subchunk2Size; /* data size */
    /* sub-chunk-data */
//    Data_block_t block;
} Data_s;

typedef struct WAV_FORMAT {
   RIFF_s riff;
   FMT_s fmt;
   Data_s data;
} Wav_s;

int main(void)
{
	print("--------test--------\r\n");

	FATFS fs;	//pointer to object
	FRESULT res = f_mount(&fs, "", 0);	//Mount the default drive
	if (res != FR_OK) {
		xil_printf("fail to mount the default drive");
	}
	xil_printf("success to mount the default drive\r\n");

	DIR dp;
	FIL fp;
	FIL fp1;
	UINT bw;	//byte write
	UINT br;	//byte read

	//-------read wav file------------------------------

	//open/create a file
	f_open(&fp, "piano.wav", FA_READ);
	xil_printf("fsize = %x\r\n", fp.fsize);
	xil_printf("\n\r");
	//f_lseek(&fp, 0);
	//f_read (&fp, buffer0, 0xA00000, &br);
	//for (int i = 0; i < 0xA00000; i++){
	//	xil_printf("buffer[%x] = %x \r\n", i, buffer0[i]);}
	//xil_printf("buffer0[0] = %c \r\n", buffer0[0]);
	//xil_printf("buffer0[1] = %c \r\n", buffer0[1]);
	//xil_printf("buffer0[2] = %c \r\n", buffer0[2]);
	//xil_printf("buffer0[3] = %c \r\n", buffer0[3]);

	Wav_s wav;
	RIFF_s riff;
	FMT_s fmt;
	Data_s data;

	f_lseek(&fp, 0);
	f_read (&fp, &wav, sizeof(wav), &br);

    riff = wav.riff;
    fmt = wav.fmt;
    data = wav.data;

	//xil_printf("wav size = %d\r\n", sizeof(wav));

	xil_printf("ChunkID = %c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
	xil_printf("ChunkSize = %x\n", riff.ChunkSize);
	xil_printf("Format = %c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);
	xil_printf("\n\r");

	xil_printf("Subchunk1ID = %c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
	xil_printf("Subchunk1Size = %d\n", fmt.Subchunk1Size);
	xil_printf("AudioFormat = %d\n", fmt.AudioFormat);
	xil_printf("NumChannels = %d\n", fmt.NumChannels);
	xil_printf("SampleRate = %d\n", fmt.SampleRate);
	xil_printf("ByteRate = %d\n", fmt.ByteRate);
	xil_printf("BlockAlign = %d\n", fmt.BlockAlign);
	xil_printf("BitsPerSample = %d\n", fmt.BitsPerSample);
	xil_printf("\n\r");

	xil_printf("blockID = %c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
	xil_printf("blockSize = %x\n", data.Subchunk2Size);
	xil_printf("\n\r");

	//-------copy and paste to another wav file-------
	u8* buffer0;
	//u8* buffer1;
	//u8 buffer2;
	//xil_printf("i = %d\n", fp.fsize/0x2F000);
	//xil_printf("last byte = %x\r\n", fp.fsize - (0x2F000*18));

	//2F000 byte maximum read with FATfs
	f_open(&fp1, "joe.wav", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	f_lseek(&fp, 0);
	f_lseek(&fp1, 0);

	//2F000 byte maximum read with FATfs
	f_read (&fp, buffer0, sizeof(wav), &br);
	f_write (&fp1, buffer0, sizeof(wav), &bw);
	xil_printf("RIFF chunk and fmt chunk writing:\n");
	xil_printf("pointer position = %x; end or not:%d ; byte wrote = %x\r\n", f_tell(&fp), f_eof (&fp), bw);

	xil_printf("data chunk writing:\n");
	for (int i = 0; i < ((fp.fsize - sizeof(wav)) / 0x2F000); i++){
		f_read (&fp, buffer0, 0x2f000, &br);
		//-------do some filters design here using buffer0-----




		//-----------------------------------------------------
		f_write (&fp1, buffer0, 0x2f000, &bw);
		xil_printf("pointer position = %x; end or not:%d ; byte wrote = %x\r\n", f_tell(&fp), f_eof (&fp), bw);
	}

	//xil_printf("last = %x\n", (fp.fsize - sizeof(wav)) - (0x2F000* ((fp.fsize - sizeof(wav)) / 0x2F000)));
	f_read (&fp, buffer0, (fp.fsize - sizeof(wav)) - (0x2F000* ((fp.fsize - sizeof(wav)) / 0x2F000)), &br);
	f_write (&fp1, buffer0, (fp.fsize - sizeof(wav)) - (0x2F000* ((fp.fsize - sizeof(wav)) / 0x2F000)), &bw);
	xil_printf("pointer position = %x; end or not:%d ; byte wrote = %x\r\n", f_tell(&fp), f_eof (&fp), bw);

	xil_printf("\n\r");

	//-------read new wav file------------------------------
	f_lseek(&fp1, 0);
	f_read (&fp1, &wav, sizeof(wav), &br);
	xil_printf("new fsize = %x\r\n", fp1.fsize);

	riff = wav.riff;
	fmt = wav.fmt;
	data = wav.data;

	//xil_printf("wav size = %d\r\n", sizeof(wav));

	xil_printf("ChunkID = %c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
	xil_printf("ChunkSize = %x\n", riff.ChunkSize);
	xil_printf("Format = %c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);
	xil_printf("\n\r");

	xil_printf("Subchunk1ID = %c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
	xil_printf("Subchunk1Size = %d\n", fmt.Subchunk1Size);
	xil_printf("AudioFormat = %d\n", fmt.AudioFormat);
	xil_printf("NumChannels = %d\n", fmt.NumChannels);
	xil_printf("SampleRate = %d\n", fmt.SampleRate);
	xil_printf("ByteRate = %d\n", fmt.ByteRate);
	xil_printf("BlockAlign = %d\n", fmt.BlockAlign);
	xil_printf("BitsPerSample = %d\n", fmt.BitsPerSample);
	xil_printf("\n\r");

	xil_printf("blockID = %c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
	xil_printf("blockSize = %x\n", data.Subchunk2Size);
	xil_printf("\n\r");


	f_close(&fp);
	f_close(&fp1);
	xil_printf("----done----\r\n");

    return XST_SUCCESS;
}
