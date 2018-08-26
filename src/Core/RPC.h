/*
Copyright(C) 2018 Brandan Tyler Lasley

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
*/
#pragma once
#include <string>
#include <vector>
#include <string>

#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include "cereal/cereal.hpp"

// Methods
#define RPC_METHOD_GET_BALANCE              "getbalance"
#define RPC_METHOD_GET_ADDRESS              "getaddress"
#define RPC_METHOD_GET_BLK_HEIGHT           "getheight"
#define RPC_METHOD_TRANSFER                 "transfer"
#define RPC_METHOD_SWEEP_ALL                "sweep_all"
#define RPC_METHOD_GET_TRANSFERS            "get_transfers"
#define RPC_METHOD_CREATE_WALLET            "create_wallet"
#define RPC_METHOD_OPEN_WALLET              "open_wallet"
#define RPC_METHOD_CLOSE_RPC                "stop_wallet"
#define RPC_METHOD_STORE                    "store"
#define RPC_METHOD_RESCAN_SPENT             "rescan_spent"
#define RPC_METHOD_GET_TX_NOTE              "get_tx_notes"
#define RPC_METHOD_SET_TX_NOTE              "set_tx_notes"

struct BalanceRet
{
    std::uint64_t   Balance;
    std::uint64_t   UnlockedBalance;
};

struct TransferRet
{
    std::uint64_t   fee;
    std::string     tx_hash;
    std::string     tx_key;
};

struct TransferItem
{
    std::string tx_hash;
    std::uint64_t amount;
    mutable std::uint64_t payment_id;
    unsigned int block_height;

    friend bool operator<(const struct TransferItem & lhs, const struct TransferItem & rhs)
    {
        return lhs.block_height > rhs.block_height;
    }
};

struct TransferItemCmp {
    bool operator() (const struct TransferItem & lhs, const struct TransferItem & rhs) const
    {
        return lhs.block_height > rhs.block_height;
    }
};

struct TransferList
{
    std::multiset<struct TransferItem, TransferItemCmp> tx_in;
    std::multiset<struct TransferItem, TransferItemCmp> tx_out;
};

class RPC
{
public:
    RPC();
    RPC(const RPC & obj);
    void                            open(unsigned short _port);


    struct BalanceRet               getBalance(int id = 0) const;
    std::string                     getAddress(int id = 0) const;
    unsigned int                    getBlockHeight(int id = 0) const;
    TransferRet                     tranfer(std::uint64_t payment_id, std::uint64_t amount, const std::string & address, int id = 0) const;
    TransferRet                     sweepAll(std::uint64_t payment_id, const std::string & address, int id = 0) const;
    TransferRet                     tranfer(const std::string & payment_id, std::uint64_t amount, const std::string & address, int id = 0) const;
    TransferRet                     sweepAll(const std::string & payment_id, const std::string & address, int id = 0) const;
    TransferList                    getTransfers(int id = 0) const;
    bool                            createWallet(const std::string & name, const std::string & password = {}, const std::string & language = "English", int id = 0) const;
    bool                            openWallet(const std::string & name, const std::string & password = {}, int id = 0) const;
    void                            stopWallet(int id = 0) const;
    void                            store(int id = 0) const;
    void                            rescanSpent(int id = 0) const;
    void                            setTXNote(const std::vector<std::string> & txVect, const std::vector<std::string> & noteVect, int id = 0) const;
    std::vector<std::string>        getTXNote(const std::vector<std::string> & txVect, int id = 0) const;

    unsigned short                  getPort() const;

    RPC&                            operator=(const RPC &rhs);

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(CEREAL_NVP(port));
    }
private:
    unsigned short                    port;

    void                            handleNetworkError(const std::string & msg) const;
    void                            handleRPCError(Poco::DynamicStruct error) const;
    Poco::DynamicStruct             getDataFromRPC(const std::string & method, const Poco::DynamicStruct & args, int id = 0) const;
};