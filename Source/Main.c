#include "..\Include\CoffeLdr.h"
#include "..\Include\BeaconApi.h"
#include "..\Include\Utils.h"

int main( int argc, char* argv[] )
{
    PCHAR  File   = NULL;
    PCHAR  Entry  = NULL;
    DWORD  Status = 0;
    SIZE_T Size   = 0;
    PVOID  Memory = NULL;
    PCHAR  Output = NULL;
    unsigned char* arguments = NULL;
    int argumentSize = 0;

    puts( "[*] CoffeeLdr: Beacon Object loader by @C5pider" );

    if ( argc < 2 )
    {
        printf( "[!] Specify an object file\n"
                "[*] Help:\n"
                "   %s [entrypoint] [file]", argv[ 0 ] );

        return 0;
    }

    Entry  = argv[ 1 ];
    File   = argv[ 2 ];

    printf( "[+] File => %s\n", File );

    Memory = LoadFileIntoMemory( File, &Size );
    if ( ! Memory )
    {
        printf( "[!] Couldn't load file: %d\n", GetLastError() );
        return 0;
    }

    if (argc == 4) {
        arguments = unhexlify((unsigned char*)argv[3], &argumentSize);
    }


    Status = CoffeeLdr( Entry, Memory, arguments, argumentSize );

    Output = BeaconGetOutputData( NULL );
    if ( Output != NULL)
        printf("[*] Beacon Output:\n\n%s\n", Output);
    else
        puts( "[*] Not beacon output" );

    if ( Memory )
    {
        memset( Memory, 0, Size );
        LocalFree( Memory );
        Memory = NULL;
    }

    printf( "[*] Status => %d\n", Status );
}