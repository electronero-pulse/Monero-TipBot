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
#include "cereal/cereal.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/archives/json.hpp"
#include "types.h"

#define VERSION_MAJOR                           2
#define VERSION_MINOR                           8

struct AboutConfig
{
    unsigned int major;
    unsigned int minor;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(major),
            CEREAL_NVP(minor)
        );
    }
};

struct GeneralConfig
{
    std::string             discordToken;
    bool                    Quitting;
    bool                    Shutdown;
    unsigned int            Threads;
    std::vector<DiscordID>  Admins;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(discordToken),
            CEREAL_NVP(Admins)
        );
    }
};

struct RPCConfig
{
    std::string             json_uri;
    std::string             wallet_path;
    double                  coin_offset;
    unsigned char           mixin;
    std::string             coin_abbv;
    unsigned short          address_length;
    unsigned short          sub_address_length;
    unsigned short          integrated_address_length;
    std::string             filename;
    std::string             hostname;
    std::string             daemon_hostname;
    bool                    use_test_net;

    template <class Archive>
    void save(Archive & ar) const
    {
        ar(
            CEREAL_NVP(json_uri),
            CEREAL_NVP(wallet_path),
            CEREAL_NVP(coin_offset),
            CEREAL_NVP(mixin),
            CEREAL_NVP(coin_abbv),
            CEREAL_NVP(address_length),
            CEREAL_NVP(sub_address_length),
            CEREAL_NVP(integrated_address_length),
            CEREAL_NVP(filename),
            CEREAL_NVP(hostname),
            CEREAL_NVP(daemon_hostname),
            CEREAL_NVP(use_test_net)
        );
    }

    template <class Archive>
    void load(Archive & ar);
};

struct RPCManagerConfig
{
    unsigned short          starting_port_number;
    unsigned short          max_rpc_limit;
    unsigned char           error_giveup;
    time_t                  blockchain_save_time;
    time_t                  search_for_new_transactions_time;
    time_t                  wallets_save_time;
    time_t                  wallet_watchdog_time;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(starting_port_number),
            CEREAL_NVP(max_rpc_limit),
            CEREAL_NVP(error_giveup),
            CEREAL_NVP(blockchain_save_time),
            CEREAL_NVP(search_for_new_transactions_time),
            CEREAL_NVP(wallets_save_time),
            CEREAL_NVP(wallet_watchdog_time)
        );
    }
};

struct FacuetConfig
{
    double                  percentage_allowance;
    std::uint64_t           min_discord_account;
    std::uint64_t           timeout;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(percentage_allowance),
            CEREAL_NVP(min_discord_account),
            CEREAL_NVP(timeout)
        );
    }
};

struct LotteryConfig
{
    double                  ticket_cost;
    double                  donation_percent;
    double                  no_winner_chance;
    unsigned char           day;
    unsigned char           close;
    unsigned char           pick;
    unsigned char           faucet;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(ticket_cost),
            CEREAL_NVP(donation_percent),
            CEREAL_NVP(no_winner_chance),
            CEREAL_NVP(day),
            CEREAL_NVP(close),
            CEREAL_NVP(pick),
            CEREAL_NVP(faucet)
        );
    }
};

struct ChatRewardsConfig
{
    std::uint64_t next_drawing_time;
    std::uint64_t next_payment_time;

    template <class Archive>
    void serialize(Archive & ar)
    {
        ar(
            CEREAL_NVP(next_drawing_time),
            CEREAL_NVP(next_payment_time)
        );
    }
};

class AppConfig
{
public:
    AppConfig();
    void load_config(const std::string & file);
    void save_config();

    struct AboutConfig          About;
    struct GeneralConfig        General;
    struct RPCConfig            RPC;
    struct RPCManagerConfig     RPCManager;
    struct FacuetConfig         Faucet;
    struct LotteryConfig        Lottery;
    struct ChatRewardsConfig    ChatRewards;

    template <class Archive>
    void save(Archive & ar) const
    {
        ar(
            CEREAL_NVP(About),
            CEREAL_NVP(General),
            CEREAL_NVP(RPC),
            CEREAL_NVP(RPCManager),
            CEREAL_NVP(Faucet),
            CEREAL_NVP(Lottery),
            CEREAL_NVP(ChatRewards)
        );
    }

    template <class Archive>
    void load(Archive & ar);

private:
    std::string currentConfig;
};

extern AppConfig GlobalConfig;


template <class Archive>
void AppConfig::load(Archive & ar)
{
    ar(
        CEREAL_NVP(About),
        CEREAL_NVP(General),
        CEREAL_NVP(RPC),
        CEREAL_NVP(RPCManager),
        CEREAL_NVP(Faucet),
        CEREAL_NVP(Lottery)
    );

    if (GlobalConfig.About.major > 2 || GlobalConfig.About.major >= 2 && GlobalConfig.About.minor > 5)
    {
        ar(
            CEREAL_NVP(ChatRewards)
        );
    }
}

template <class Archive>
void RPCConfig::load(Archive & ar)
{
    ar(
        CEREAL_NVP(json_uri),
        CEREAL_NVP(wallet_path),
        CEREAL_NVP(coin_offset),
        CEREAL_NVP(mixin),
        CEREAL_NVP(coin_abbv),
        CEREAL_NVP(address_length)
    );

    if (GlobalConfig.About.major > 2 || GlobalConfig.About.major >= 2 && GlobalConfig.About.minor > 7)
    {
        ar(CEREAL_NVP(sub_address_length), CEREAL_NVP(integrated_address_length));
    }

    ar(
        CEREAL_NVP(filename),
        CEREAL_NVP(hostname),
        CEREAL_NVP(daemon_hostname)
    );

    if (GlobalConfig.About.major > 2 || GlobalConfig.About.major >= 2 && GlobalConfig.About.minor > 2)
    {
        ar(CEREAL_NVP(use_test_net));
    }
}