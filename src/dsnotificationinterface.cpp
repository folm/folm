// Copyright (c) 2015 The Folm Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "dsnotificationinterface.h"
#include "obfuscation.h"
#include "masternode-budget.h"
#include "masternode-payments.h"
#include "masternode-sync.h"

CDSNotificationInterface::CDSNotificationInterface()
{
}

CDSNotificationInterface::~CDSNotificationInterface()
{
}

void CDSNotificationInterface::UpdatedBlockTip(const CBlockIndex *pindex)
{
    obfuScationPool.UpdatedBlockTip(pindex);
    mnpayments.UpdatedBlockTip(pindex);
    budget.UpdatedBlockTip(pindex);
    masternodeSync.UpdatedBlockTip(pindex);
}
