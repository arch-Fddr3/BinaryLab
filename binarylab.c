#include <stdio.h>
#include <stdbool.h>

int main( int argc, char *argv[] ) {
	FILE *bnfl;
	char hexdump[ 16 ];
	char *name = NULL;
	size_t offset = 0;

	if ( argc == 2 ) {
		name = argv[ 1 ];
	} else if ( argc > 2 ) {
		fprintf( stderr, "WARNING: Too many input\n" );
		return 1;
	} else {
		fprintf( stderr, "WARNING: No file name was given\n" );
		return 1;
	}

	bnfl = fopen( name, "rb" );
	if ( bnfl == NULL ) {
		perror( "WARNING" );
		return 1;
	}

	while ( true ) {
		size_t rdbt = fread( hexdump, 1, 16, bnfl );
		if ( rdbt == 0 ) {
			break;
		}
		printf( "%08zx ", offset );
		for ( size_t i = 0; i < 16; i++ ) {
			if ( i < rdbt ) {
				printf( "%02x ", ( unsigned char )hexdump[ i ] );
			} else {
				printf( "   " );
			}
		}
		printf( "  |  " );
		for ( size_t i = 0; i < rdbt; i++ ) {
			unsigned char ascii = ( unsigned char )hexdump[ i ];
			if ( ascii >= 32 && ascii <= 126) {
				printf( "%c", ( ascii ));
			} else {
				printf( "." );
			}
		}
		printf( "\n" );
		offset += rdbt;
	}

	fclose( bnfl );
	return 0;
}