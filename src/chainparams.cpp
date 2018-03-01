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
                (0, uint256("0x00000aec3ce04601f5a475eab9f30dfccfb1eb9076a9c6c853e07a7734809c98"))
		        (10, uint256("0x000004df093d73d11068eb52f61572bf457b0925aa78f74ab2287832be42fc12"))
		        (500, uint256("0x00000000000b9160602ee8949d8c5cdffb5cb261ee4a66add0ca1686815cf54c"))
		        (5000, uint256("0x00000000001044f5653026712e9af65c74a4a0878afb848de05e458625c8187a"))
		        (7200, uint256("0x0000000000057bd12ed10785d6636299dc4840360b40f3126b59e9f997e069ea"));

static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1519887793,// * UNIX timestamp of last checkpoint block
        9054,    // * total number of transactions between genesis and last checkpoint
        //   (the tx=... number in the SetBestChain debug.log lines)
        2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1518900000,
        0,
        250};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        1518900000,
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
        vAlertPubKey = ParseHex("042da06568454d47e0b2349c6953b069690d13fd501e081ee8679cf4a0daaacb7c131f640048df4275a9fa172b34f12349856624031f76a56096aa1a");
        nDefaultPort = 53656;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Folm starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 2 * 60; // Folm: 2 minutes
        nTargetSpacingSlowLaunch = 3 * 60;  // Folm: 3 minutes for first day
        nTargetSpacing = 2* 60; // Folm: 2 mins
        nLastPOWBlock = 26280000; // 100 Years
        nRampToBlock = 500; // Slow start, ramp linearly to this block
        nMaturity = 49; // 98 Minutes
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 22739116 * COIN; // Year 2050

        const char* pszTimestamp = "17 February 2018 - Folm Coin - Week of chaos, again, engulfs Trump";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040e3fe58595206cf8c5612c977e10335393b689ead98cda8c0e4e29e5377b628ff6de54ca1936ac57072ce70968ee5202b91ddd53bc4f8f2baa8640") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1518900000;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1809743;

        hashGenesisBlock = genesis.GetHash();

        vFixedSeeds.clear();
        vSeeds.clear();
        assert(hashGenesisBlock == uint256("0x00000aec3ce04601f5a475eab9f30dfccfb1eb9076a9c6c853e07a7734809c98"));
        assert(genesis.hashMerkleRoot == uint256("0x985190fcf993fea0ab74ca2e9cc59300469055edd73512ef23bb01cce0aaea81"));

        vSeeds.push_back(CDNSSeedData("folm-node10.folmcoin.com", "folm-node10.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node09.folmcoin.com", "folm-node09.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node08.folmcoin.com", "folm-node08.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node07.folmcoin.com", "folm-node07.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node06.folmcoin.com", "folm-node06.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node05.folmcoin.com", "folm-node05.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node04.folmcoin.com", "folm-node04.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node03.folmcoin.com", "folm-node03.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node02.folmcoin.com", "folm-node02.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node01.folmcoin.com", "folm-node01.folmcoin.com"));

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
        strSporkKey = "0425a68d2a8b1f375f69926ff68c8350982d2890984d4b09e118cc29e6359ae1caf0669ecef05b671fb75b8452cb30a7d36d09ccb9693988510fc547";
        strObfuscationPoolDummyAddress = "FZS69ngaE5dAgT3K6mGTu4AmrNwFB1si6r";
        nStartMasternodePayments = 1518900000;
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

        vAlertPubKey = ParseHex("048b8e440b71f26bbd54808da0c19cb4eece2b839afe5749876525ecd183120ce4fc57adee9ee4456843c074afd32ef42048e4504b8503e5ac7e9bf4");
        nDefaultPort = 43246;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // 120 Seconds
        nTargetSpacing = 5 * 120;  // 600 Seconds
        nLastPOWBlock = 1000;
        nMaturity = 15;
        nMaxMoneyOut = 33284220 * COIN; // 2050 Maximum

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1518900000;
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
