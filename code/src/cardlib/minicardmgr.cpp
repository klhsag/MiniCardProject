
#include "minicardmgr.h"

CardLink StdCardSet::create_auto(){
    if (id_pool.empty()){
        id_pool[0] = false;
    }
    int next_int = id_pool.rbegin()->first + 1;
    id_pool[next_int] = true;
    auto newCard = std::make_shared<StdMiniCard>();
    newCard->setData("id", next_int);
    card_map.insert({next_int, newCard});
    return newCard.get();
}

CardLink StdCardSet::create_by_id(int id){
    auto it = id_pool.find(id);
    if (it==id_pool.end()){
        id_pool[id] = false;
        it = id_pool.find(id);
    }
    if (it->second) return CardLink();//nullptr;
    it->second = true;
    auto newCard = std::make_shared<StdMiniCard>();
    newCard->setData("id", id);
    card_map.insert({id, newCard});
    return newCard.get();
}

void StdCardSet::delete_by_id(int id){
    auto it = card_map.find(id);
    if (it==card_map.end()) return;
    it->second->setCaption("delete", "delete");
    card_map.erase(it);
    id_pool[id] = false;
}

CardLink StdCardSet::at(int index){
    auto it = card_map.find(index);
    if (it==card_map.end()) return CardLink();//nullptr;
    return it->second.get();
}
