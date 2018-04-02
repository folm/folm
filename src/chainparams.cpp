// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2016 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Folm developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


/**
    * Build the genesis block. Note that the output of its generation
    * transaction cannot be spent since it did not originally exist in the
    * database.
    *
    * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
    *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
    *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
    *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
    *   vMerkleTree: e0028e
 */

//! Convert the pnSeeds6 array into usable address objects.
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "17 February 2018 - Folm Coin - Week of chaos, again, engulfs Trump";
    const CScript genesisOutputScript = CScript() << ParseHex("042da06568454d47e0b2349c6953b069690d13fd501e081ee8679cf4a0daaacb7c131f640048df4275a9fa172b34f12349856624031f76a56096aa1a71fe47b66f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}
/**
 * Main network
 */
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {

        strNetworkID = "main";
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 2 * 60 * 24; // Dash: 48 Minutes
        consensus.nPowTargetSpacing = 2 * 60; // Dash: 2 minutes
        consensus.nTargetSpacingSlowLaunch = 3 * 60; // Folm: 3 minutes for first day
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nLastPOWBlock = 26280000; // 100 Years
        consensus.nRampToBlock = 500; // 100 Years
        consensus.nMaturity = 49; // 98 Minutes
        consensus.nMasternodeCountDrift = 4;
        consensus.nModifierUpdateBlock = 1;
        pchMessageStart[0] = 0x66;
        pchMessageStart[1] = 0x6f;
        pchMessageStart[2] = 0x6c;
        pchMessageStart[3] = 0x6d;
        vAlertPubKey = ParseHex("042da06568454d47e0b2349c6953b069690d13fd501e081ee8679cf4a0daaacb7c131f640048df4275a9fa172b34f12349856624031f76a56096aa1a71fe47b66f");
        nDefaultPort = 53656;
        nMaxTipAge = 0x7fffffff;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1518900000, 1809743, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256("0x00000aec3ce04601f5a475eab9f30dfccfb1eb9076a9c6c853e07a7734809c98"));
        assert(consensus.genesis.hashMerkleRoot == uint256("0x985190fcf993fea0ab74ca2e9cc59300469055edd73512ef23bb01cce0aaea81"));

        vSeeds.push_back(CDNSSeedData("folm-node01.folmcoin.com", "folm-node01.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node02.folmcoin.com", "folm-node02.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node03.folmcoin.com", "folm-node03.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node04.folmcoin.com", "folm-node04.folmcoin.com"));
        vSeeds.push_back(CDNSSeedData("folm-node05.folmcoin.com", "folm-node05.folmcoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 36); // Folm address start with F
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 36);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 178);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x15)(0x2A)(0x21)(0x13).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x03)(0x33)(0x4C)(0xAF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0xED)(0xFF)(0x89)(0x00).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

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
        strSporkKey = "0425a68d2a8b1f375f69926ff68c8350982d2890984d4b09e118cc29e6359ae1caf0669ecef05b671fb75b8452cb30a7d36d09ccb9693988510fc547ee45c904ce";
        strObfuscationPoolDummyAddress = "FZS69ngaE5dAgT3K6mGTu4AmrNwFB1si6r";
        nStartMasternodePayments = 1518900000;
        checkpointData = (CCheckpointData) {
                boost::assign::map_list_of
                (    0, uint256S("0x00000aec3ce04601f5a475eab9f30dfccfb1eb9076a9c6c853e07a7734809c98"))
                (   10, uint256S("0x000004df093d73d11068eb52f61572bf457b0925aa78f74ab2287832be42fc12"))
                (  500, uint256S("0x00000000000b9160602ee8949d8c5cdffb5cb261ee4a66add0ca1686815cf54c"))
                ( 5000, uint256S("0x00000000001044f5653026712e9af65c74a4a0878afb848de05e458625c8187a"))
                ( 7200, uint256S("0x0000000000057bd12ed10785d6636299dc4840360b40f3126b59e9f997e069ea"))
                (10802, uint256S("0x0000000000033d9285e516da50779f81268240047904c4e1377c5ad39ec9d6ac"))
                (15425, uint256S("0x0000000000003b88cd7ae706ad099d7854e43ce6c591c86c6c8ec241d4560525"))
                (29188, uint256S("0x00000000001fbc3653a666bb03237dab2b39e8e5da680be8f87247dae9a54d0e")),
                1522663981,// * UNIX timestamp of last checkpoint block
                46062,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
                2000        // * estimated number of transactions per day after checkpoint
        };

    }
};
static CMainParams mainParams;

//TODO Fix testnet
/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams
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

        vAlertPubKey = ParseHex("048b8e440b71f26bbd54808da0c19cb4eece2b839afe5749876525ecd183120ce4fc57adee9ee4456843c074afd32ef42048e4504b8503e5ac7e9bf41efdefac6f");
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
        strSporkKey = "0425a68d2a8b1f375f69926ff68c8350982d2890984d4b09e118cc29e6359ae1caf0669ecef05b671fb75b8452cb30a7d36d09ccb9693988510fc547ee45c904ce";
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
class CRegTestParams : public CChainParams
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

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    default:
            throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
    }
}
void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
