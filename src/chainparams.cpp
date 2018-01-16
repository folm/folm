// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Folm developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
        (0, uint256("0x"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1516104913,// * UNIX timestamp of last checkpoint block
    1,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1516104913,
    0,
    250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1516104913,
    0,
    100};
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x66;
        pchMessageStart[1] = 0x6f;
        pchMessageStart[2] = 0x6c;
        pchMessageStart[3] = 0x6d;
	    vAlertPubKey = ParseHex("04ea69dbe4752e60c4ed0252ae823bbab6e80e6ac6b254b87fbf15c7af6d2b602462e0fe8f0d4c4b450fa68da95706c297c5e600a56d03d1c4bfbaed416ef739f4");
        nDefaultPort = 53656;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Folm starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // Folm: 2 minutes
        nTargetSpacingSlowLaunch = 5 * 120;  // Folm: 10 minutes (Slow launch - Block 300)
	    nTargetSpacing = 2 * 60; // Folm: 2 mins after block 300
        nLastPOWBlock = 8409600; // 32 Years
	    nRampToBlock = 960; // Slow start, ramp linearly to this block
        nMaturity = 49; // 98 Minutes
	    nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
	    nMaxMoneyOut = 22739116 * COIN; // Year 2050

        const char* pszTimestamp = "16 October 2018 - Folm coin started test alpha";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("046a17cf3ab7199f92ff254b59c618269bd3499d0adc3377678d9e967d6e4222be654dd3ecb5d3037123ce4f17c5035528a150ce6c28d5378ee56c2d4b2b50dd4c") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1516104913;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();;
        genesis.nNonce = 0;

        hashGenesisBlock = genesis.GetHash();
        hashGenesisBlock == uint256("0x");
        genesis.hashMerkleRoot == uint256("0x");

		vSeeds.push_back(CDNSSeedData("mempool.pw", "flmseed.mempool.pw"));
        vSeeds.push_back(CDNSSeedData("ssus.tech", "folm-dns-seed04.ssus.tech"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 36); // Folm address start with F
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 36);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 178);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x15)(0x2A)(0x21)(0x13).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0x33)(0x4C)(0xAF).convert_to_container<std::vector<unsigned char> >();
        //  BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0xED)(0xFF)(0x89)(0x00).convert_to_container<std::vector<unsigned char> >();
        
	    convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        
	    fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        
	    nPoolMaxTransactions = 3;
        strSporkKey = "04d35db018d163f596b73a3256b0c5e53eff499760ca0acb32ea5a7c5a8616bbb61d2bb4df1a0fbfc4b69b6d9da1734f4ab89406f9a94088acee9c5f771b508b60";
        strObfuscationPoolDummyAddress = "FZS69ngaE5dAgT3K6mGTu4AmrNwFB1si6r";
        nStartMasternodePayments = 1516104913;
    }


    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xa0;

	    vAlertPubKey = ParseHex("0451267d0a6d698c6fa8c3b7f1b0dbe94e76d4af39e9e7a130e83d411331d4f032d62009751e4d2782eb92e9df32db859ade18860826c7a97836cd6c1a1b713577");
        nDefaultPort = 43246;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // 120 Seconds
        nTargetSpacing = 5 * 120;  // 600 Seconds
        nLastPOWBlock = 1000;
        nMaturity = 15;
	    nMaxMoneyOut = 33284220 * COIN; // 2050 Maximum

	//! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1511311453;
        genesis.nNonce = 746269;
	    genesis.nBits = bnProofOfWorkLimit.GetCompact();

	    hashGenesisBlock == uint256("0x");
	    genesis.hashMerkleRoot == uint256("0x");
        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("folm.io", "test01.folm.io"));
	    vSeeds.push_back(CDNSSeedData("folm.io", "test02.folm.io"));
	    vSeeds.push_back(CDNSSeedData("folm.io", "test03.folm.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65); // Testnet folm addresses start with 'T'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet folm script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet folm BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet folm BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet folm BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "04d35db018d163f596b73a3256b0c5e53eff499760ca0acb32ea5a7c5a8616bbb61d2bb4df1a0fbfc4b69b6d9da1734f4ab89406f9a94088acee9c5f771b508b60";
        strObfuscationPoolDummyAddress = "TUQ57Fbh1crybrDhV6X9SDH95H4oSq4v6p";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Folm: 1 day
        nTargetSpacing = 1 * 60;        // Folm: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 52589;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 52591;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;
static CChainParams* pCurrentParams = 0;
CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}
const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}
