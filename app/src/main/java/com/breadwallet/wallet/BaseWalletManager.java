package com.breadwallet.wallet;

import android.content.Context;

//import com.breadwallet.core.BRCoreAddress;
//import com.breadwallet.core.BRCoreMerkleBlock;
//import com.breadwallet.core.BRCorePeer;
//import com.breadwallet.core.BRCorePeerManager;
//import com.breadwallet.core.BRCoreTransaction;
//import com.breadwallet.core.BRCoreWallet;
import com.breadwallet.presenter.entities.CurrencyEntity;
//import com.breadwallet.presenter.entities.TxUiHolder;
//import com.breadwallet.wallet.wallets.configs.WalletUiConfiguration;

import java.math.BigDecimal;
import java.util.List;


/**
 * BreadWallet
 * <p/>
 * Created by Mihail Gutan on <mihail@breadwallet.com> 1/22/18.
 * Copyright (c) 2018 breadwallet LLC
 * <p/>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * <p/>
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * <p/>
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
public interface BaseWalletManager {

//    public BaseWalletManager(BRCoreMasterPubKey masterPubKey,
//                      BRCoreChainParams chainParams,
//                      double earliestPeerTime) {
//        super(masterPubKey, chainParams, earliestPeerTime);
//    }



    //get the currency symbol e.g. Bitcoin - ₿, Ether - Ξ
    String getSymbol(Context app);

    //get the currency denomination e.g. Bitcoin - BTC, Ether - ETH
    String getIso(Context app);

    //get the currency scheme (bitcoin or bitcoincash)
//    String getScheme(Context app);

    //get the currency name e.g. Bitcoin
    String getName(Context app);


}
