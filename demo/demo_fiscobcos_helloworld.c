/******************************************************************************
 * Copyright (C) 2018-2021 aitos.io
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#define  USE_CREATE_PERSIST_WALLET //if expect create a persist wallet, uncomment this definition
//#define  USE_LOAD_PERSIST_WALLET   // if expect load a persist wallet, uncomment this definition


#include "boatiotsdk.h"

#if PROTOCOL_USE_FISCOBCOS == 1
#include "HelloWorld.h"

BoatFiscobcosWallet *g_fiscobcos_wallet_ptr;


#if defined( USE_CREATE_PERSIST_WALLET )
__BOATSTATIC BOAT_RESULT fiscobcos_createPersistWallet(BCHAR *wallet_name)
{
    BSINT32 index;
    BoatFiscobcosWalletConfig wallet_config = {0};

	/* wallet_config value assignment */
    //native format demoKey is "fcf6d76706e66250dbacc9827bc427321edb9542d58a74a67624b253960465ca"
    char * demoKey =  "-----BEGIN EC PRIVATE KEY-----\n"
                      "MHQCAQEEIPz212cG5mJQ26zJgnvEJzIe25VC1Yp0pnYkslOWBGXKoAcGBSuBBAAK\n"
                      "oUQDQgAEMU/3IAjKpQc8XdURIGQZZJQRHZhPDkp80ahiRAM7KKV9Gmn699pei5fL\n"
                      "qZlYLvlxdQJsoh2IPyObgGr87gBT7w==\n"
                      "-----END EC PRIVATE KEY-----\n";

	/* wallet_config value assignment */
    wallet_config.prikeyCtx_config.prikey_genMode = BOAT_WALLET_PRIKEY_GENMODE_EXTERNAL_INJECTION;
    wallet_config.prikeyCtx_config.prikey_format  = BOAT_WALLET_PRIKEY_FORMAT_PKCS;
    wallet_config.prikeyCtx_config.prikey_type    = BOAT_WALLET_PRIKEY_TYPE_SECP256K1;
    memcpy(wallet_config.prikeyCtx_config.prikey_content, demoKey, strlen(demoKey) );
    wallet_config.prikeyCtx_config.prikey_content_length = strlen(demoKey) + 1; //length contain terminator
    
    strncpy( wallet_config.node_url_str, "http://127.0.0.1:8545", BOAT_NODE_URL_MAX_LEN - 1 );

	/* create fiscobcos wallet */
    index = BoatWalletCreate(BOAT_PROTOCOL_FISCOBCOS, wallet_name, &wallet_config, sizeof(BoatFiscobcosWalletConfig));
    if( index == BOAT_ERROR )
	{
        BoatLog(BOAT_LOG_CRITICAL, "create persist wallet failed.");
        return BOAT_ERROR;
    }

    g_fiscobcos_wallet_ptr = BoatGetWalletByIndex( index );

    return BOAT_SUCCESS;
}
#endif

#if defined( USE_LOAD_PERSIST_WALLET )
__BOATSTATIC BOAT_RESULT fiscobcos_loadPersistWallet(BCHAR *wallet_name)
{
	BSINT32 index;

	/* create fiscobcos wallet */
    index = BoatWalletCreate(BOAT_PROTOCOL_FISCOBCOS, wallet_name, NULL, sizeof(BoatFiscobcosWalletConfig));
    if( index == BOAT_ERROR )
	{
        BoatLog(BOAT_LOG_CRITICAL, "load wallet failed.");
        return BOAT_ERROR;
    }
    g_fiscobcos_wallet_ptr = BoatGetWalletByIndex( index );

    return BOAT_SUCCESS;
}
#endif

BOAT_RESULT fiscobcos_helloworld(BoatFiscobcosWallet *wallet_ptr)
{
    BCHAR           *result_str;
    BoatFiscobcosTx tx_ctx;
    BOAT_RESULT     result;
    
    /* Set Contract Address */
    result = BoatFiscobcosTxInit(wallet_ptr, &tx_ctx, BOAT_TRUE, 
								 "0x11E1A300", //gasprice
							     "0x33333333", //gaslimit
							     "0x22506bd03b8130913efa2f0b6b1db60a2fcda9ff", //recipient
								 "0x01", //chainid
								 "0x01"  //groupid
								);
    if( result != BOAT_SUCCESS )
	{
        BoatLog(BOAT_LOG_NORMAL, "BoatFiscobcosTxInit fails.");
        return BOAT_ERROR;
    }

    result_str = HelloWorld_set(&tx_ctx, "HELLO FISCOBCOS!");
    if( result_str == NULL )
	{
        BoatLog(BOAT_LOG_NORMAL, "HelloWorld_set failed: %s.", result_str);
		return BOAT_ERROR;
    }
	BoatLog(BOAT_LOG_NORMAL, "set returns: %s", result_str);
    
    result_str = HelloWorld_get(&tx_ctx);
    if( result_str == NULL )
	{
        BoatLog(BOAT_LOG_NORMAL, "HelloWorld_get failed: %s.", result_str);
		return BOAT_ERROR;
    }
	BoatLog(BOAT_LOG_NORMAL, "get returns: %s", result_str);
	
    return BOAT_SUCCESS;
}

int main(int argc, char *argv[])
{
	BOAT_RESULT  result  = BOAT_SUCCESS;

	/* step-1: Boat SDK initialization */
    BoatIotSdkInit();
    
	/* step-2: create fiscobcos wallet */
#if defined( USE_CREATE_PERSIST_WALLET )
	BoatLog(BOAT_LOG_NORMAL, ">>>>>>>>>> wallet type: create persist wallet.");
	result = fiscobcos_createPersistWallet("fiscobcos.cfg");
#elif defined( USE_LOAD_PERSIST_WALLET )
	BoatLog(BOAT_LOG_NORMAL, ">>>>>>>>>> wallet type: load persist wallet.");
	result = fiscobcos_loadPersistWallet("fiscobcos.cfg");
#else
	BoatLog(BOAT_LOG_NORMAL, ">>>>>>>>>> none wallet type selected.");
	return -1;
#endif	
    if( result != BOAT_SUCCESS )
	{
		 BoatLog(BOAT_LOG_CRITICAL, "fiscobcosWalletPrepare_create failed : %d.", result);
		return -1;
	}
    
	/* step-3: execute 'fiscobcos_call_helloworld' */
	result += fiscobcos_helloworld( g_fiscobcos_wallet_ptr );
    if( result != BOAT_SUCCESS )
	{
        BoatLog(BOAT_LOG_NORMAL, "fiscobcos helloworld access Failed: %d.", result);
    }
	else
	{
        BoatLog(BOAT_LOG_NORMAL, "fiscobcos helloworld access Passed.");
    }
	
	/* step-4: Boat SDK Deinitialization */
    BoatIotSdkDeInit();
    
    return 0;
}
#else
int main(int argc, char *argv[])
{
    BoatLog(BOAT_LOG_NORMAL, "undefine PROTOCOL_USE_FISCOBCOS");
    return 0;
}
#endif /* end of PROTOCOL_USE_FISCOBCOS */
