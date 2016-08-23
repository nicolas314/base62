#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char * base62_digits="0123456789"
                            "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;

char * b62_encode(uint64_t num)
{
    /* 64 bits is up to 11 digits in base 62 */
    static char enc[15] ;
    int         i, len ;
    uint64_t    rem ;
    char        c ;

    /* Zero out output buffer */
    memset(enc, 0, sizeof(enc));
    if (num==0) {
        enc[0]='0';
        return enc;
    }
    i=0 ;
    while (num>0) {
        rem = num % 62 ;
        enc[i] = base62_digits[rem];
        i++ ;
        num /= 62 ;
    }
    /* Reverse string */
    len = (int)strlen(enc);
    for (i=0 ; i<len/2 ; i++) {
        c = enc[i] ;
        enc[i] = enc[len-i-1];
        enc[len-i-1] = c ;
    }
    return enc ;
}

uint64_t b62_decode(char * s)
{
    uint64_t    num ;
    uint64_t    p ;
    char     *  pos ;
    int         i ;

    if (!s)
        return 0 ;

    p=1;
    num=0;
    for (i=strlen(s)-1 ; i>=0 ; i--) {
        pos = strchr(base62_digits, (int)s[i]);
        if (!pos) {
            return 0 ;
        }
        num += (uint64_t)(pos-base62_digits) * p ;
        p *= 62 ;
    }
    return num ;
}

#ifdef MAIN
int main(int argc, char * argv[])
{
    uint64_t num ;
    char * s ;

	if (argc<2) {
		printf("use: %s\n", argv[0]);
		return 1 ;
	}

    sscanf(argv[1], "%llu", &num);
    s   = b62_encode(num);
    printf("base62: %s\n", s);
    num = b62_decode(s);
    printf("dec: %llu\n", num);
	return 0 ;
}
#endif

