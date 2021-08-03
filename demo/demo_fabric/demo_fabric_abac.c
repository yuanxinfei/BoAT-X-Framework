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
#if defined(__unix__) || defined(__unix) || defined(unix)
	/* for timestamp source */
	#define _POSIX_C_SOURCE 200809L
	#include <time.h>
#endif
#include "boatconfig.h"
#include "boatiotsdk.h"

// const BCHAR * fabric_client_demokey  = "-----BEGIN PRIVATE KEY-----\n"
// 			 						   "MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgZv0mwHQMEGry976y\n"
// 									   "yJK38MQq+s98MpPmkKCAxAYLm8+hRANCAAT8KxmQX+3tjzRp1KBJmT02inKXNLyE\n"
// 									   "8zyXeva18ib+GgF0Iu9VwydQQ9OPUJcHDDXFUARk/neouR+EhJwXzl98\n"
// 									   "-----END PRIVATE KEY-----\n";

// crypto-config\peerOrganizations\org1.example.com\users\User1@org1.example.com\msp\keystore
const BCHAR *fabric_client_demokey = 	"-----BEGIN PRIVATE KEY-----\n"
										"MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgRXwC/eQa+OBeKL5v\n"
										"uVKC/0S9FvTCwu/hEBvev+p6vByhRANCAAQ3vxr92n486LOD5SA3eqoZtDU+6zL2\n"
										"rNrzxDm3XHbEfyMpmXM/1xsGyn6CbICIkXcp7MwMCknOXlUTAUqNw9jR\n"
										"-----END PRIVATE KEY-----\n"
										"\n";
//crypto-config\peerOrganizations\org1.example.com\users\User1@org1.example.com\msp\signcerts
const BCHAR * fabric_client_democert =  "-----BEGIN CERTIFICATE-----\n"
										"MIICKjCCAdCgAwIBAgIQe4aLzXY6K/mNOqIonVWiOjAKBggqhkjOPQQDAjBzMQsw\n"
										"CQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMNU2FuIEZy\n"
										"YW5jaXNjbzEZMBcGA1UEChMQb3JnMS5leGFtcGxlLmNvbTEcMBoGA1UEAxMTY2Eu\n"
										"b3JnMS5leGFtcGxlLmNvbTAeFw0yMTA2MDIwMTQ2MDBaFw0zMTA1MzEwMTQ2MDBa\n"
										"MGwxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1T\n"
										"YW4gRnJhbmNpc2NvMQ8wDQYDVQQLEwZjbGllbnQxHzAdBgNVBAMMFlVzZXIxQG9y\n"
										"ZzEuZXhhbXBsZS5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAAQ3vxr92n48\n"
										"6LOD5SA3eqoZtDU+6zL2rNrzxDm3XHbEfyMpmXM/1xsGyn6CbICIkXcp7MwMCknO\n"
										"XlUTAUqNw9jRo00wSzAOBgNVHQ8BAf8EBAMCB4AwDAYDVR0TAQH/BAIwADArBgNV\n"
										"HSMEJDAigCBG0APEm2XnhkKrhtp5j+n39naV2w7rMgfPRr3KdkdbQjAKBggqhkjO\n"
										"PQQDAgNIADBFAiEAtL1CHAyYAxbM0VzqRNur0ax3zC/Lovg3xttUsScejlUCIFUP\n"
										"0uFbWIIaahaThZ4hvjIdO/jN7t8iI55xreOj1DMy\n"
										"-----END CERTIFICATE-----\n";

//crypto-config\peerOrganizations\org1.example.com\peers\peer0.org1.example.com\msp\cacerts
const BCHAR * fabric_ca1_democert    =  "-----BEGIN CERTIFICATE-----\n"
										"MIICUjCCAfigAwIBAgIRAMK02x10K2inOT0rPU0iPk4wCgYIKoZIzj0EAwIwczEL\n"
										"MAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcTDVNhbiBG\n"
										"cmFuY2lzY28xGTAXBgNVBAoTEG9yZzEuZXhhbXBsZS5jb20xHDAaBgNVBAMTE2Nh\n"
										"Lm9yZzEuZXhhbXBsZS5jb20wHhcNMjEwNjAyMDE0NjAwWhcNMzEwNTMxMDE0NjAw\n"
										"WjBzMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMN\n"
										"U2FuIEZyYW5jaXNjbzEZMBcGA1UEChMQb3JnMS5leGFtcGxlLmNvbTEcMBoGA1UE\n"
										"AxMTY2Eub3JnMS5leGFtcGxlLmNvbTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IA\n"
										"BGr7NR1CAK6VbFp42UN4z+jPbyLhhTGVhlKuV4wrGcWsk4ciivPcy8SD0nJbl2Xv\n"
										"amuNNYXdWZKKxbXUt6UY9gijbTBrMA4GA1UdDwEB/wQEAwIBpjAdBgNVHSUEFjAU\n"
										"BggrBgEFBQcDAgYIKwYBBQUHAwEwDwYDVR0TAQH/BAUwAwEB/zApBgNVHQ4EIgQg\n"
										"RtADxJtl54ZCq4baeY/p9/Z2ldsO6zIHz0a9ynZHW0IwCgYIKoZIzj0EAwIDSAAw\n"
										"RQIhANXVF2ecIvDqGa7QHKReAgnhDI8wyTWxap/RVeJ/HW0JAiAZy64jeX2frsOK\n"
										"P4o22DenRX0U2rN3nu05lYMhQZMqtA==\n"
										"-----END CERTIFICATE-----\n";
//crypto-config\peerOrganizations\org2.example.com\peers\peer0.org2.example.com\msp\cacerts
const BCHAR * fabric_ca2_democert    =  "-----BEGIN CERTIFICATE-----\n"
										"MIICUjCCAfigAwIBAgIRANaRg8qTA6mwtLvq/tWZizEwCgYIKoZIzj0EAwIwczEL\n"
										"MAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcTDVNhbiBG\n"
										"cmFuY2lzY28xGTAXBgNVBAoTEG9yZzIuZXhhbXBsZS5jb20xHDAaBgNVBAMTE2Nh\n"
										"Lm9yZzIuZXhhbXBsZS5jb20wHhcNMjEwNjAyMDE0NjAwWhcNMzEwNTMxMDE0NjAw\n"
										"WjBzMQswCQYDVQQGEwJVUzETMBEGA1UECBMKQ2FsaWZvcm5pYTEWMBQGA1UEBxMN\n"
										"U2FuIEZyYW5jaXNjbzEZMBcGA1UEChMQb3JnMi5leGFtcGxlLmNvbTEcMBoGA1UE\n"
										"AxMTY2Eub3JnMi5leGFtcGxlLmNvbTBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IA\n"
										"BOQSs6qq6+G9ICrLbZYJPGPDlGiqbXu9YRhqHHtCYyhpmUjm1Ptk5N3CxSMIPj19\n"
										"6b+UDrp8fkoJl9ZONb10IGOjbTBrMA4GA1UdDwEB/wQEAwIBpjAdBgNVHSUEFjAU\n"
										"BggrBgEFBQcDAgYIKwYBBQUHAwEwDwYDVR0TAQH/BAUwAwEB/zApBgNVHQ4EIgQg\n"
										"T2CxwctZ0AhRo3NQeXX6ry+14tnBJYwaVzsiufa1fJ0wCgYIKoZIzj0EAwIDSAAw\n"
										"RQIhANw0vv2KaTLIm5kos7qftzvz+O2o4Z4N6pgx2bX5BaDoAiAegqxREsi5sy8o\n"
										"xiLcaGYPlCF6/0XrDx9ZwmGUfYQ5nw==\n"
										"-----END CERTIFICATE-----\n";
//crypto-config\ordererOrganizations\example.com\orderers\orderer.example.com\msp\cacerts
const BCHAR * fabric_ca3_democert    =  "-----BEGIN CERTIFICATE-----\n"
										"MIICPjCCAeSgAwIBAgIRANWz0LWPRf8zPXMl/K2HIsEwCgYIKoZIzj0EAwIwaTEL\n"
										"MAkGA1UEBhMCVVMxEzARBgNVBAgTCkNhbGlmb3JuaWExFjAUBgNVBAcTDVNhbiBG\n"
										"cmFuY2lzY28xFDASBgNVBAoTC2V4YW1wbGUuY29tMRcwFQYDVQQDEw5jYS5leGFt\n"
										"cGxlLmNvbTAeFw0yMTA2MDIwMTQ2MDBaFw0zMTA1MzEwMTQ2MDBaMGkxCzAJBgNV\n"
										"BAYTAlVTMRMwEQYDVQQIEwpDYWxpZm9ybmlhMRYwFAYDVQQHEw1TYW4gRnJhbmNp\n"
										"c2NvMRQwEgYDVQQKEwtleGFtcGxlLmNvbTEXMBUGA1UEAxMOY2EuZXhhbXBsZS5j\n"
										"b20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAASBUHr/87wNzx77vbs6UKoh29kG\n"
										"QR4CH3eFmuBUgHDsDO8mt2T35AYUQRQGh00himD6v6VEABdstWEUV3ne+TjNo20w\n"
										"azAOBgNVHQ8BAf8EBAMCAaYwHQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMB\n"
										"MA8GA1UdEwEB/wQFMAMBAf8wKQYDVR0OBCIEIF8tm9BNAWLIUtV4uXsk/QBOEcWc\n"
										"SzSe1q88PwRRsWiRMAoGCCqGSM49BAMCA0gAMEUCIQCBjtuqZteYc3SWw21l2vXs\n"
										"42Qnv3mu6VFXGRsj9Os2bQIgFaq/f0XTGBYL63h2x2NDHQlqBJ6OS7XgvkF7PT5B\n"
										"gVM=\n"
										"-----END CERTIFICATE-----\n";

const BCHAR * fabric_demo_endorser1_url      = "139.224.234.74:7051";
const BCHAR * fabric_demo_endorser1_hostName = "peer0.org1.example.com";
const BCHAR * fabric_demo_endorser2_url      = "139.224.234.74:9051";
const BCHAR * fabric_demo_endorser2_hostName = "peer0.org2.example.com";
const BCHAR * fabric_demo_order1_url         = "139.224.234.74:7050";
const BCHAR * fabric_demo_order1_hostName    = "orderer.example.com";

BoatHlfabricWallet *g_fabric_wallet_ptr;

__BOATSTATIC BOAT_RESULT fabricWalletPrepare(void)
{
	BOAT_RESULT index;

	BoatHlfabricWalletConfig wallet_config = {0};
	//set private key context
	wallet_config.accountPriKey_config.prikey_genMode = BOAT_WALLET_PRIKEY_GENMODE_EXTERNAL_INJECTION;
	wallet_config.accountPriKey_config.prikey_type    = BOAT_WALLET_PRIKEY_TYPE_SECP256R1;
	wallet_config.accountPriKey_config.prikey_format  = BOAT_WALLET_PRIKEY_FORMAT_PKCS;
	wallet_config.accountPriKey_config.prikey_content.field_ptr = (BUINT8 *)fabric_client_demokey;
	wallet_config.accountPriKey_config.prikey_content.field_len = strlen(fabric_client_demokey) + 1; //length contain terminator

	//set cert context
	wallet_config.accountCertContent.length = strlen(fabric_client_democert) + 1;
	memcpy(wallet_config.accountCertContent.content , fabric_client_democert, wallet_config.accountCertContent.length);

	//set rootCA info
	wallet_config.rootCaNumber = 3;
	wallet_config.rootCaContent[0].length  = strlen(fabric_ca1_democert) + 1;
	memcpy(wallet_config.rootCaContent[0].content , fabric_ca1_democert,wallet_config.rootCaContent[0].length );
	wallet_config.rootCaContent[1].length  = strlen(fabric_ca2_democert) + 1;
	memcpy(wallet_config.rootCaContent[1].content , fabric_ca2_democert,wallet_config.rootCaContent[1].length );
	wallet_config.rootCaContent[2].length  = strlen(fabric_ca3_democert) + 1;
	memcpy(wallet_config.rootCaContent[2].content , fabric_ca3_democert,wallet_config.rootCaContent[2].length );

	//set endorser info
	wallet_config.endorserNumber = 2;
	memcpy(wallet_config.endorser[0].nodeUrl , fabric_demo_endorser1_url, strlen(fabric_demo_endorser1_url) + 1);
	memcpy(wallet_config.endorser[0].hostName, fabric_demo_endorser1_hostName, strlen(fabric_demo_endorser1_hostName) + 1);
	memcpy(wallet_config.endorser[1].nodeUrl , fabric_demo_endorser2_url, strlen(fabric_demo_endorser2_url) + 1);
	memcpy(wallet_config.endorser[1].hostName, fabric_demo_endorser2_hostName, strlen(fabric_demo_endorser2_hostName) + 1);

	//set orderer info
	wallet_config.ordererNumber = 1;
	memcpy(wallet_config.orderer[0].nodeUrl , fabric_demo_order1_url, strlen(fabric_demo_order1_url) + 1);
	memcpy(wallet_config.orderer[0].hostName, fabric_demo_order1_hostName, strlen(fabric_demo_order1_hostName) + 1);

	/* create fabric wallet */
#if defined( USE_ONETIME_WALLET )
	index = BoatWalletCreate( BOAT_PROTOCOL_HLFABRIC, NULL, &wallet_config, sizeof(BoatHlfabricWalletConfig) );
#elif defined( USE_CREATE_PERSIST_WALLET )
	index = BoatWalletCreate( BOAT_PROTOCOL_HLFABRIC, "fabric.cfg", &wallet_config, sizeof(BoatHlfabricWalletConfig) );
#elif defined( USE_LOAD_PERSIST_WALLET )
	index = BoatWalletCreate( BOAT_PROTOCOL_HLFABRIC, "fabric.cfg", NULL, sizeof(BoatHlfabricWalletConfig) );
#else
	return BOAT_ERROR;
#endif
	if(index == BOAT_ERROR)
	{
		//BoatLog( BOAT_LOG_CRITICAL, "fabricWalletPrepare failed." );
		return BOAT_ERROR;
	}
	g_fabric_wallet_ptr = BoatGetWalletByIndex( index );

	return BOAT_SUCCESS;
}

int main(int argc, char *argv[])
{
	BOAT_RESULT       result  = BOAT_SUCCESS;
	BoatHlfabricTx    tx_ptr;

	/* step-1: Boat SDK initialization */
    BoatIotSdkInit();

	/* step-2: prepare wallet */
	result = fabricWalletPrepare();
	if( result != BOAT_SUCCESS )
	{
		//BoatLog( BOAT_LOG_CRITICAL, "fabricWalletPrepare failed." );
		return -1;
	}

	/* step-3: fabric transaction structure initialization */
	result = BoatHlfabricTxInit( &tx_ptr, g_fabric_wallet_ptr, NULL, "mycc", NULL, "mychannel", "Org1MSP" );
	if( result != BOAT_SUCCESS )
	{
		//BoatLog( BOAT_LOG_CRITICAL, "BoatHlfabricTxInit failed." );
		return -1;
	}

	/* step-4: set transaction timestamp */
#if defined(__unix__) || defined(__unix) || defined(unix)
	struct timespec txTimestamp;
	clock_gettime(CLOCK_REALTIME, &txTimestamp);
	result = BoatHlfabricTxSetTimestamp( &tx_ptr, txTimestamp.tv_sec, txTimestamp.tv_nsec );
#else
	long int timesec = 0;
	time(&timesec);
	result = BoatHlfabricTxSetTimestamp( &tx_ptr, timesec, 0 );
#endif
	if( result != BOAT_SUCCESS )
	{
		//BoatLog( BOAT_LOG_CRITICAL, "BoatHlfabricTxSetTimestamp failed." );
		return -1;
	}

	/* step-5: set transaction 'invoke' command */
	result += BoatHlfabricTxSetArgs( &tx_ptr, "invoke", "a", "b", "10", NULL );
	result += BoatHlfabricTxSubmit( &tx_ptr );
	if( result != BOAT_SUCCESS )
	{
		//BoatLog( BOAT_LOG_CRITICAL, "BoatHlfabricTxSubmit(invoke) failed." );
		return -1;
	}

	/* step-6: wait seconds and 'query' the tansaction */
	BoatSleep(3);
	result += BoatHlfabricTxSetArgs( &tx_ptr, "query", "a", NULL );
	result += BoatHlfabricTxEvaluate( &tx_ptr );
	if( result != BOAT_SUCCESS )
	{
		//BoatLog( BOAT_LOG_CRITICAL, "BoatHlfabricTxSubmit(query) failed." );
		return -1;
	}

	/* step-7: fabric transaction structure Deinitialization */
	BoatHlfabricTxDeInit( &tx_ptr );

	/* step-8: Boat SDK Deinitialization */
    BoatIotSdkDeInit();

    return 0;
}