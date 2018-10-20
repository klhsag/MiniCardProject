#pragma once

#include "stdminicard.h"

class StdCardSet{

public:
    StdCardSet() = default;
    ~StdCardSet() = default;
    StdCardSet(const StdCardSet &) = delete;
    StdCardSet(StdCardSet &&) = delete;
    StdCardSet & operator=(const StdCardSet &) = delete;
    StdCardSet & operator=(StdCardSet &&) = delete;

    CardLink create_auto();
    CardLink create_by_id(int);
    void delete_by_id(int);

    CardLink at(int);

private:
    std::map<int, bool> id_pool;
    std::map<int, std::shared_ptr<StdMiniCard> > card_map;
};
