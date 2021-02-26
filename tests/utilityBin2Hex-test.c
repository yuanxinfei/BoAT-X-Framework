#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "boattypes.h"
#include "boatutility.h"


int main(int argc, char *argv[])
{
	BCHAR    to_str[128];
	BUINT8   from_str[128];
	BUINT32  from_str_len;
	
	memset(to_str  , 0, sizeof(to_str)/sizeof(to_str[0]));
	memset(from_str, 0, sizeof(from_str)/sizeof(from_str[0]));
	from_str[0]  = 0x00;
    from_str[1]  = 0x00;
	from_str[2]  = 0x01;
	from_str[3]  = 0xAB;
	from_str_len = 4;

	UtilityBin2Hex(to_str, from_str, from_str_len, BIN2HEX_LEFTTRIM_QUANTITY, BIN2HEX_PREFIX_0x_YES, BOAT_FALSE);
	printf("BIN2HEX_LEFTTRIM_QUANTITY = %s\n", to_str);
	UtilityBin2Hex(to_str, from_str, from_str_len, BIN2HEX_LEFTTRIM_ZEROBYTE, BIN2HEX_PREFIX_0x_YES, BOAT_FALSE);
	printf("BIN2HEX_LEFTTRIM_ZEROBYTE = %s\n", to_str);
	UtilityBin2Hex(to_str, from_str, from_str_len, BIN2HEX_LEFTTRIM_UNFMTDATA, BIN2HEX_PREFIX_0x_YES, BOAT_FALSE);
	printf("BIN2HEX_LEFTTRIM_UNFMTDATA = %s\n", to_str);
	
	return 0;
}
