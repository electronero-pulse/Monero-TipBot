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
#include "Language.h"
#include <utility>
#include <functional>

class LanguageSelect GlobalLanguage; 

#define LANGPAIR(n, t) std::make_pair(n,t)
LanguageSelect::LanguageSelect()
{
    LocalLanguage =
    {
        {
            { "English",
                {
                    // TIP
                    LANGPAIR("TIP_HELP_COMMAND","TipBot Commands:\\n"),
                    LANGPAIR("TIP_BALANCE","%s#%s: Your Balance is %0.8f %s and your Unlocked Balance is %0.8f %s"),
                    LANGPAIR("TIP_ADDRESS","%s#%s: Your %s Address is: %s"),
                    LANGPAIR("TIP_HISTORY_HEADER","```Amount | User | Block Height | TX Hash\\n"),
                    LANGPAIR("TIP_HISTORY_INC_HEADER","Your Incoming Transactions (last 5): \\n"),
                    LANGPAIR("TIP_HISTORY_OUT_HEADER","\\nYour Outgoing Transactions (last 5): \\n"),
                    LANGPAIR("TIP_WITHDRAW_SUCCESS","%s#%s: Withdraw Complete Sent %0.8f %s with TX Hash: %s :smiley:"),
                    LANGPAIR("TIP_WITHDRAW_SUSPENDED","%s#%s: Withdraws aren't allowed at the moment."),
                    LANGPAIR("TIP_GIVE_SUCESS","%s#%s: Giving %0.8f %s to %s with TX Hash: %s :smiley:"),
                    LANGPAIR("TIP_GIVE_SUSPENDED","%s#%s: Give isn't allowed at the moment. :cold_sweat:"),
                    LANGPAIR("TIP_BLOCK_HEIGHT","Your wallet's current block height is: %?i"),
                    LANGPAIR("TIP_WALLET_RESTART_SUCCESS","Discord Wallet restarted successfully! It may take a minute to resync."),
                    LANGPAIR("TIP_WITHDRAW_TOGGLE","Withdraw Enabled: %b"),
                    LANGPAIR("TIP_GIVE_TOGGLE","Give Enabled: %b"),
                    LANGPAIR("TIP_RESCAN_SUCCESS","Rescan spent complete!"),
                    LANGPAIR("TIP_TOTAL_BALANCE","I currently manage %0.8f locked %s and %0.8f unlocked %s! (Excluding lottery)"),
                    LANGPAIR("TIP_WALLET_SAVE_SUCCESS","Wallets saved!"),
                    LANGPAIR("TIP_FAUCET_RESTART_SUCCESS","Faucet Restarted!"),
                    LANGPAIR("TIP_RESTART_SUCCESSS","Restart Command sent!"),
                    LANGPAIR("TIP_SHUTDOWN_SUCCESSS","Shutdown Command sent! -- Good bye."),
                    LANGPAIR("TIP_WHOIS_USER","User %?i is %s"),
                    LANGPAIR("TIP_WHOIS_USER_NOT_FOUND","Unknown!"),
                    LANGPAIR("TIP_LIST_LANGUAGE","Language List:\\n"),
                    LANGPAIR("TIP_LIST_LANGUAGE_FORMAT","%?i. %s\\n"),
                    LANGPAIR("TIP_LANGUAGE_SELECT_SUCCESS","Language Changed Successfully!\\n"),
                    LANGPAIR("TIP_LANGUAGE_SELECT_FAIL","Invalid Language!\\n"),


                    // LOTTERY
                    LANGPAIR("LOTTERY_WINNER","The winner is %?i"),
                    LANGPAIR("LOTTERY_GAME_INFO","Game Info:\\n```Minimum Ticket Cost %f %s\\nFaucet Donation: %f%% of the reward\\nNo Winner: %f%% of the drawing will be no winner.\\nDays: Lottery starts on %s 00:00 UTC and end on %s %?i UTC. Winners announced on %s %?i UTC\\nIn the event of no winner the jackpot is rolled over to next drawing\\nWinner will be direct messaged.\\n```"),
                    LANGPAIR("LOTTERY_HELP","Lottery Commands:\\n"),
                    LANGPAIR("LOTTERY_JACKPOT","The current jackpot is: %0.8f"),
                    LANGPAIR("LOTTERY_BUY_TICKET_SUCCESS","%s#%s: Purchased %?i tickets for %0.8f %s with TX Hash: %s :smiley:"),
                    LANGPAIR("LOTTERY_SUSPENDED","Lottery is currently suspended."),
                    LANGPAIR("LOTTERY_CLOSED","Lottery is closed until 12 AM UTC."),
                    LANGPAIR("LOTTERY_TICKETS","You currently have %Lu active tickets."),
                    LANGPAIR("LOTTERY_WON_WITH_WINNER","There was a winner last lottery!"),
                    LANGPAIR("LOTTERY_WON_WITHOUT_WINNER","There was no winner last lottery!"),
                    LANGPAIR("LOTTERY_LAST_WINNER","The last winner was: %?i"),
                    LANGPAIR("LOTTERY_SUSPEND_TOGGLE","Lottery Enabled: %b"),
                    LANGPAIR("LOTTERY_USER_WON", "You've won %0.8f %s from the lottery! :money_with_wings:"),

                    // Faucet
                    LANGPAIR("FAUCET_HELP","Faucet Commands (use ``!give [amount] @Tip Bot`` to donate to faucet):\\n"),
                    LANGPAIR("FAUCET_TAKE_SUCCESS","%s#%s: You have been granted %0.8f %s with TX Hash: %s :smiley:\\n"),
                    LANGPAIR("FAUCET_TAKE_PENDING_TRANSACTIONS","Bot has pending transactions, try again later. :disappointed_relieved: \\n"),
                    LANGPAIR("FAUCET_TAKE_IS_BROKE","Bot is broke, try again later. :disappointed_relieved:\\n"),
                    LANGPAIR("FAUCET_TAKE_TOO_SOON","Too soon! You're allowed one ``!take`` every %?i hours, remaining %f hours."),
                    LANGPAIR("FAUCET_TAKE_ACCOUNT_NOT_MATURE","Your Discord account must be older than 7 days.\\n"),
                    LANGPAIR("FAUCET_TAKE_DISABLED","Faucet Disabled!\\n"),

                    // Chat Rewards
                    LANGPAIR("CHAT_REWARDS_PAYMENT", "User %?i has been chosen and added to the payment queue."),

                    // Projects 
                    LANGPAIR("PROJECTS_HELP","Projects Help Menu"),
                    LANGPAIR("PROJECTS_ERROR_EXISTS","Error project already exists!"),
                    LANGPAIR("PROJECTS_ERROR_GOAL_ZERO","Project goal cannot be zero!"),
                    LANGPAIR("PROJECTS_CREATED_SUCCESS","Project created successfully!"),
                    LANGPAIR("PROJECTS_NOT_EXIST","Error project doesn't exist!"),
                    LANGPAIR("PROJECTS_DELETE_SUCCESS","Project deleted successfully!"),
                    LANGPAIR("PROJECTS_GRANT_SUCCESS","Transfering all funds from project %s to user %s with tx hash %s"),
                    LANGPAIR("PROJECTS_TOGGLE_STATUS","Project Status : %b"),
                    LANGPAIR("PROJECTS_FUND_SUCCESS","Sending %0.8f %s to project %s with tx hash %s"),
                    LANGPAIR("PROJECTS_SUSPENDED","Project Suspended!"),
                    LANGPAIR("PROJECTS_LIST_HEADER","Project, Descrption, Goal, Percentage Funded, Suspended\\n"),
                    LANGPAIR("PROJECTS_VIEW_STATUS_LIST","%s:\\n```Description: %s\\nBalance: %0.8f %s\\nUnlocked Balance: %0.8f %s\\nGoal: %0.8f %s\\nPercentage Complete: %0.2f%%```"),
                    LANGPAIR("PROJECTS_DIRECT_ADDRESS","%s's Direct Address: %s"),
                    LANGPAIR("PROJECTS_NO_PROJECTS","No Projects!"),
                }
            }
        }
    };
}

const std::string & LanguageSelect::getString(uint8_t language, const std::string & label)
{
    return LocalLanguage[language].LangMap[label];
}

void LanguageSelect::getLanguages(std::vector<std::string> & vect)
{
    for (const auto & l : LocalLanguage)
        vect.emplace_back(l.LangName);
}

size_t LanguageSelect::size()
{
    return LocalLanguage.size();
}

