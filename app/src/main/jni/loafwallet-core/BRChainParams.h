//
//  BRChainParams.h
//
//  Created by Aaron Voisine on 1/10/18.
//  Copyright (c) 2019 breadwallet LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.

#ifndef BRChainParams_h
#define BRChainParams_h

#include "BRMerkleBlock.h"
#include "BRSet.h"
#include <assert.h>

typedef struct {
    uint32_t height;
    UInt256 hash;
    uint32_t timestamp;
    uint32_t target;
} BRCheckPoint;

typedef struct {
    const char * const *dnsSeeds; // NULL terminated array of dns seeds
    uint16_t standardPort;
    uint32_t magicNumber;
    uint64_t services;
    int (*verifyDifficulty)(const BRMerkleBlock *block, const BRSet *blockSet); // blockSet must have last 2016 blocks
    const BRCheckPoint *checkpoints;
    size_t checkpointsCount;
} BRChainParams;


static const char *BRMainNetDNSSeeds[] = {
    "seed.peristeri.xyz",
    "seed.pigeoncoin.xyz",
    "australiacash.org",
    "157.230.41.76"
//    "192.99.19.160",
//    "60.191.146.186",
//    "78.128.77.167",
//    "78.40.84.53",
//    "95.30.239.250",
//    "58.171.135.242",
//    "167.114.135.147",
//    "207.81.246.219",
//    "94.45.223.47",
//    "193.70.35.149",
//    "111.73.46.97",
//    "178.238.224.253"
};

static const char *BRTestNetDNSSeeds[] = {
    "seed.pigeoncoin.org",
    "seed2.pigeoncoin.org",
    "seed3.pigeoncoin.org",
    "seed4.pigeoncoin.org"
};

// blockchain checkpoints - these are also used as starting points for partial chain downloads, so they must be at
// difficulty transition boundaries in order to verify the block difficulty at the immediately following transition
static const BRCheckPoint BRMainNetCheckpoints[] = {
//    {       0, u256_hex_decode("000000f049bef9fec0179131874c54c76c0ff59f695db30a4f0da52072c99492"), 1521661111, 0x1e00ffff },
//    {       25420, u256_hex_decode("000000000015f99026409fc469f23b7f327381241ef46e682850c27e4354fe3d"), 1522250411, 0x1b5ecec0 },
//    {       50420, u256_hex_decode("0000000000059b106a3bec49488bc6c6e271e56517cf8ff77ccf80595406abfe"), 1523928659, 0x1b2b8935 },
//    {       87570,  u256_hex_decode("0000000000639a9468641873ceab00c1fbce7e2f895d7bcf6563bf2d02d2d049"), 1528605889, 0x1c009163 },
//    {      111222, u256_hex_decode("00000000002925cd877a54b28c959e8ac12c341e238539cf117d8ed2a77fd828"), 1533482872, 0x1c01bef6 },
//    {      166222, u256_hex_decode("00000000009a33113ed94cb847bf1cafb6f998a7e19cbd5eace85fb2c1baada0"), 1536778628, 0x1c00b883 },
//    {      211222, u256_hex_decode("000000000077d73073e149b82b3e2422d8db140712a3e7e6296d44931a033d5b"), 1539480333, 0x1c00e62b },
//    {      320000, u256_hex_decode("00000000005c58a9bc3d746bc91d0a14f81f7adaa229daa7ab5de810a6b404ae"), 1546005073, 0x1c00ded5 },
//    {      420000, u256_hex_decode("00000000001f7e2a7a26728db0ffec8a3d0690e824200b648519b3ce52ebfeca"), 1552004467, 0x1c00d30a },
//    {      520000, u256_hex_decode("0000000000302a242a763e9c07821b23ba1cb762a4bb3ce474bdf9ee964859f9"), 1558004994, 0x1c0098ef }, // x16r blocks unusable due to fork
    {      740000, u256_hex_decode("00000000001da7cc7b451e5b4f23944ed0278ba31f4835adfa7fa782276ace48"), 1571207863, 0x1b271eac }, // Approx x21s fork start block
    {      750000, u256_hex_decode("00000000001a253ae36bebd689e04301306e7aa1a3bc86cec8119e8ac638ff73"), 1571808191, 0x1b20b6ef }

};

static const BRCheckPoint BRTestNetCheckpoints[] = {
    {       0, u256_hex_decode("000000f049bef9fec0179131874c54c76c0ff59f695db30a4f0da52072c99492"), 1521661111, 0x1d00ffff }
//still need to add these
};

static int BRMainNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    const BRMerkleBlock *previous, *b = NULL;
    uint32_t i;

    assert(block != NULL);
    assert(blockSet != NULL);

    // check if we hit a difficulty transition, and find previous transition block
    if ((block->height % BLOCK_DIFFICULTY_INTERVAL) == 0) {
        for (i = 0, b = block; b && i < BLOCK_DIFFICULTY_INTERVAL; i++) {
            b = BRSetGet(blockSet, &b->prevBlock);
        }
    }

    previous = BRSetGet(blockSet, &block->prevBlock);
    return BRMerkleBlockVerifyDifficulty(block, previous, (b) ? b->timestamp : 0);
}

static int BRTestNetVerifyDifficulty(const BRMerkleBlock *block, const BRSet *blockSet)
{
    return 1; // XXX skip testnet difficulty check for now
}

static const BRChainParams BRMainNetParams = {
    BRMainNetDNSSeeds,
    8757,       // standardPort
    0x334d5a1e, // magicNumber
    0,          // services
    BRMainNetVerifyDifficulty,
    BRMainNetCheckpoints,
    sizeof(BRMainNetCheckpoints)/sizeof(*BRMainNetCheckpoints)
};

static const BRChainParams BRTestNetParams = {
    BRTestNetDNSSeeds,
    8757,      // standardPort
    0x334d5a1e, // magicNumber
    0,          // services
    BRTestNetVerifyDifficulty,
    BRTestNetCheckpoints,
    sizeof(BRTestNetCheckpoints)/sizeof(*BRTestNetCheckpoints)
};

#endif // BRChainParams_h
