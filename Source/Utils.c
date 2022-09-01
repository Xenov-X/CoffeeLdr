#include "..\Include\Utils.h"

LPVOID LoadFileIntoMemory( LPSTR Path, PDWORD MemorySize )
{
    HANDLE  hFile       = NULL;
    LPVOID  ImageBuffer = NULL;
    DWORD   dwBytesRead = 0;

    hFile = CreateFileA( Path, GENERIC_READ, 0, 0, OPEN_ALWAYS, 0, 0 );
    if ( hFile == INVALID_HANDLE_VALUE )
    {
        printf("Error opening %s\r\n", Path);
        return NULL;
    }

    if ( MemorySize )
        *MemorySize = GetFileSize( hFile, 0 );
    ImageBuffer = (PBYTE)LocalAlloc( LPTR, *MemorySize );

    ReadFile( hFile, ImageBuffer, *MemorySize, &dwBytesRead, 0 );
    return ImageBuffer;
}

DWORD HashString( PVOID String, SIZE_T Length )
{
    ULONG  Hash = HASH_KEY;
    PUCHAR Ptr  = String;

    do
    {
        UCHAR character = *Ptr;

        if ( ! Length )
        {
            if ( !*Ptr ) break;
        }
        else
        {
            if ( (ULONG) ( Ptr - (PUCHAR)String ) >= Length ) break;
            if ( !*Ptr ) ++Ptr;
        }

        if ( character >= 'a' )
            character -= 0x20;

        Hash = ( ( Hash << 5 ) + Hash ) + character;
        ++Ptr;
    } while ( TRUE );

    return Hash;
}

unsigned char* unhexlify(unsigned char* value, int* outlen) {
    unsigned char* retval = NULL;
    char byteval[3] = { 0 };
    int counter = 0;
    int counter2 = 0;
    char character = 0;
    if (value == NULL) {
        return NULL;
    }
    //DEBUG_PRINT("Unhexlify Strlen: %lu\n", (long unsigned int)strlen((char*)value));
    if (value == NULL || strlen((char*)value) % 2 != 0) {
        //DEBUG_PRINT("Either value is NULL, or the hexlified string isn't valid\n");
        goto errcase;
    }

    retval = calloc(strlen((char*)value) + 1, 1);
    if (retval == NULL) {
        goto errcase;
    }

    counter2 = 0;
    for (counter = 0; counter < strlen((char*)value); counter += 2) {
        memcpy(byteval, value + counter, 2);
        character = strtol(byteval, NULL, 16);
        memcpy(retval + counter2, &character, 1);
        counter2++;
    }
    *outlen = counter2;

errcase:
    return retval;
}
