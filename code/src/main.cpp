
#include <cstdio>
#include <iostream>

#include <vector>

#include "cardlib/minicardmgr.h"

#include "diyformat/myfwd.h"

#include "randseed/randseed.h"

#include "classiccard/rolecard.h"

using namespace std;

StdCardSet card_pool; //初始化卡池

int game_id;
CardLink gameCard;

vector<int> player_ids;
vector<CardLink> playerCards;

int main() {

    gameCard = card_pool.create_auto();
    game_id = gameCard->getData("id");

    int tot_players;
    cout << "At the beginning, input the player numbers: ";
    do {
        cin >> tot_players;
    } while (tot_players <= 0);
    cout << "Game Start! (players are numbered from 0 to " << tot_players - 1 << ")" << endl;

    gameCard->setData("player_total", tot_players);
    for (int i = 0; i<tot_players; ++i) {
        auto newptr = card_pool.create_auto();
        playerCards.push_back(newptr);
        int newid = newptr->getData("id");
        player_ids.push_back(newid);
        gameCard->setData(str_with_int("player_by_id", i), newid);

        int attack = 5 + next_rand(5);
        int defense = next_rand(5);
        int health = 6 + next_rand(6);
        rolecard::rolecardInitialize(newptr, {
            {
                {"attack", attack},
                {"defense", defense},
                {"health", health}
            }, {
                {"caption", diytostr(i)},
                {"items", "attack|defense|health"},
            }
        });
    }

    gameCard->setAction("prepareDamage", [&](StdMiniCard * self, CardAgrsPackage args) {
        int src_id = args.data["source_id"];
        int tgt_id = args.data["target_id"];
        auto src_player = card_pool.at(src_id);
        auto tgt_player = card_pool.at(tgt_id);
        if (!src_player || !tgt_player) return CardAgrsPackage();
        int damage = src_player->getData("attack") - tgt_player->getData("defense");
        if (damage<0) damage = 0;
        args.data["damage_digit"] = damage;
        return args;
    });

    int cur_vt_p = next_rand(tot_players);
    while (true) {
        for (int i = cur_vt_p; i < cur_vt_p + tot_players; ++i) {
            int p = i%tot_players;
            if (playerCards[p]->checkTag("die")) {
                cout << "# player " << playerCards[p]->getCaption("caption") << " is dead..\n";
                continue;
            }
            cout << playerCards[p]->takeAction("appendMeasurementMsg", {
                {},
                {
                    {"message", "your current data:\n" },
                    {"items", "attack|defense|health" }
                }
            }).caption["message"];
            cout << "Player " << playerCards[p]->getCaption("caption") << ", please choose enemy: ";
            int x;
            do {
                cin >> x;
            } while (!(x >= 0 && x < tot_players));
            if (p == x) {
                cout << "cannot commit suicide!" << endl;
                //--i;
                continue;
            } else if (playerCards[x]->checkTag("die")) {
                cout << "cannot kill the dead!" << endl;
                //--i;
                continue;
            }
            auto tmpArgs = gameCard->takeAction("prepareDamage", {
                {
                    {"source_id", player_ids[p] },
                    {"target_id", player_ids[x] }
                }
            });
            tmpArgs = playerCards[x]->takeAction("sufferDamage", tmpArgs);
            cout << tmpArgs.caption["message"];
            cur_vt_p = i + 1;
        }
        break;
    }
// 有某一圈无人死亡时游戏结束
    cout << "Game Ende." << endl;
    cout << "The Survivors: " << endl;
    for (int i = 0; i < tot_players; ++i) {
        if (playerCards[i]->checkTag("die")) continue;
        cout << "\tplayer " << i << endl;
    }
    cout << "Thanks." << endl;

    return 0;
}
