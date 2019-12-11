// Usage (encryption): MoreWays -C/c plaintext.file ciphertext.file password
// Usage (decryption): MoreWays -P/p ciphertext.file plaintext.file password
// Compiled on MacOS, Linux and *BSD.
// Talk is SO EASY, show you my GOD. WOW

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
// any password length
    unsigned long ulPasswordLength = -1;

// get password length
    while(argv[4][++ulPasswordLength]);

// The data of 256 values of key table that you can set randomly,
// yet you can freely to change to key table of 65536 values that you can set randomly,
// you can also freely to change to key table of 4294967296 values that you can set randomly,
// even if to change to key table of 18446744073709551616 values is no problem, which is only limited by the memory of your machine. WOW!
    unsigned char aucKeyTable[256] = {
          0x9A, 0x36, 0xe9, 0x15, 0xdA, 0x91, 0x6F, 0x04, 0xf9, 0x18, 0x1B, 0x68, 0x28, 0x45, 0xf4, 0xa7, 0xfF, 0x5A, 0x2F, 0xb5, 0x41, 0x7A, 0x8D, 0x85, 0x2C, 0x13, 0x57, 0x3D, 0xb3, 0x53, 0x34, 0xeE,
          0xd8, 0xcA, 0xd1, 0x25, 0xc6, 0xc7, 0x2E, 0x33, 0x73, 0xe3, 0xcE, 0x4E, 0xcD, 0x10, 0xa9, 0x5D, 0x0F, 0xaE, 0x3C, 0x62, 0xbA, 0xa8, 0x51, 0x11, 0xf2, 0xeF, 0x21, 0x0A, 0x0B, 0xe4, 0x86, 0x7C,
          0x87, 0xe0, 0x35, 0x07, 0x8B, 0x7F, 0x64, 0x55, 0x3E, 0x7E, 0x0E, 0x1A, 0x59, 0xaF, 0x8E, 0x54, 0xeA, 0x1C, 0xd5, 0xf1, 0x8A, 0x01, 0x5B, 0x95, 0x96, 0x7B, 0xa1, 0x67, 0x92, 0x7D, 0x6C, 0xbD,
          0xdD, 0x2D, 0xe1, 0x23, 0x47, 0x1E, 0xc5, 0x8C, 0xc0, 0xa3, 0x08, 0x4C, 0xb0, 0x6D, 0x9C, 0x80, 0x89, 0x94, 0x00, 0xc9, 0x84, 0xd7, 0x5F, 0x4B, 0xc3, 0x65, 0xe6, 0xaB, 0x93, 0x16, 0xf0, 0xb2,
          0xc2, 0x2B, 0xb7, 0x43, 0x52, 0x09, 0x76, 0x3B, 0x56, 0x60, 0x98, 0xb8, 0x32, 0x8F, 0xfE, 0x69, 0xa5, 0x88, 0xe7, 0x90, 0x99, 0x79, 0x48, 0xa0, 0xbC, 0x17, 0x40, 0xd6, 0xb6, 0x75, 0x39, 0x82,
          0x70, 0x4D, 0x81, 0x20, 0xeD, 0xb4, 0x0D, 0x71, 0x2A, 0xc8, 0x9D, 0xbB, 0xd4, 0x77, 0xf8, 0xd2, 0x29, 0x9E, 0x19, 0xaC, 0x42, 0xbF, 0x61, 0xcC, 0x38, 0x26, 0x27, 0x83, 0xcB, 0xd9, 0xb9, 0xaA,
          0x9F, 0x37, 0xdB, 0x02, 0x30, 0x44, 0xdC, 0x06, 0xf3, 0x74, 0x5C, 0x6B, 0xfA, 0xaD, 0xd0, 0x3A, 0x4F, 0x63, 0xbE, 0x97, 0x50, 0xeC, 0x66, 0xc1, 0xf7, 0xa4, 0xfC, 0x49, 0xe5, 0x14, 0x72, 0x58,
          0x3F, 0x4A, 0x46, 0x6A, 0xfD, 0xa2, 0x03, 0xb1, 0x31, 0xf6, 0xcF, 0xc4, 0x12, 0xfB, 0xf5, 0xdE, 0x78, 0x9B, 0x05, 0x6E, 0x22, 0x5E, 0x1F, 0xa6, 0x24, 0xdF, 0x1D, 0xe2, 0xe8, 0xd3, 0xeB, 0x0C
    };

    struct stat statFileSize;

// get plaintext file size
    stat(argv[2], &statFileSize);

    unsigned long ulFileSize = statFileSize.st_size;

// open plaintext/ciphertext file descriptor
    int iPlaintextOrCiphertextFD = open(argv[2], O_RDONLY, S_IRUSR | S_IWUSR);

    unsigned char *pucPlaintextOrCiphertext = (unsigned char*)malloc(ulFileSize);

// read data from plaintext/ciphertext file
    read(iPlaintextOrCiphertextFD, pucPlaintextOrCiphertext, ulFileSize);

    close(iPlaintextOrCiphertextFD);

// process plaintext data or ciphertext data
    for(unsigned long i = 0; i < ulFileSize; i += 256)
    {
// key table convert 8 * 32 = 256 bytes of data at a time in order to generate the random number of "JunTai" distribution
        for(unsigned long j = 0; j < 32; ++j)
        {
            unsigned long *pulKeySwap1 = (unsigned long*)aucKeyTable, *pulKeySwap2 = (unsigned long*)aucKeyTable, ulKeyTemp, ulKeyIndex;

            ulKeyIndex = (unsigned char)argv[4][j % ulPasswordLength] % 32;

            ulKeyTemp = pulKeySwap1[j];

            pulKeySwap1[j] = pulKeySwap2[ulKeyIndex];

            pulKeySwap2[ulKeyIndex] = ulKeyTemp;
        }

// use XOR, one's complement and two's complement to process the 256 bytes of plaintext data or ciphertext data at a time
        for(unsigned long k = 0; k < 256 && i + k < ulFileSize; ++k)
        {
            if(argv[1][0] == '-' && (argv[1][1] == 'C' || argv[1][1] == 'c'))
            {
                pucPlaintextOrCiphertext[i + k] ^= aucKeyTable[k];

                pucPlaintextOrCiphertext[i + k] = ~pucPlaintextOrCiphertext[i + k] + (unsigned char)argv[4][k % ulPasswordLength];

                pucPlaintextOrCiphertext[i + k] = ~pucPlaintextOrCiphertext[i + k];
            }
            else if(argv[1][0] == '-' && (argv[1][1] == 'P' || argv[1][1] == 'p'))
            {
                pucPlaintextOrCiphertext[i + k] = ~pucPlaintextOrCiphertext[i + k];

                pucPlaintextOrCiphertext[i + k] = ~pucPlaintextOrCiphertext[i + k] + (unsigned char)argv[4][k % ulPasswordLength];

                pucPlaintextOrCiphertext[i + k] ^= aucKeyTable[k];
            }
        }

// use key table value to change the password
        for(unsigned long l = 0; l < ulPasswordLength; ++l)
        {
            argv[4][l] = aucKeyTable[(unsigned char)argv[4][l]];
        }
    }

// open ciphertext/plaintext file descriptor
    iPlaintextOrCiphertextFD = open(argv[3], O_CREAT | O_WRONLY, S_IREAD | S_IWRITE);

// write data to ciphertext/plaintext file
    write(iPlaintextOrCiphertextFD, pucPlaintextOrCiphertext, ulFileSize);

    close(iPlaintextOrCiphertextFD);

    free(pucPlaintextOrCiphertext);

    return 0;
}
