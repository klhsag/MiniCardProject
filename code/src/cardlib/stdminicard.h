#pragma once

#include <string>

#include <map>

#include <functional>

#include <memory>

class StdMiniCard; // Attention, not thread safe. Please copy or move all the times.

//增强可配置性
struct CardAgrsPackage;

using CardData = int;
using CardCaption = std::string;
using CardLink = StdMiniCard * ;
using CardFunction = std::function<CardAgrsPackage(CardLink, CardAgrsPackage)>;

using CardDataMap = std::map<std::string, CardData>;
using CardCaptionMap = std::map<std::string, CardCaption>;
using CardLinkMap = std::map<std::string, CardLink>;
using CardFunctionMap = std::map<std::string, CardFunction>;

struct CardAgrsPackage {
    CardDataMap data;
    CardCaptionMap caption;
    CardLinkMap link;
    CardFunctionMap func;
};

class StdMiniCard {

public:
    StdMiniCard() = default;
    ~StdMiniCard() = default;
    StdMiniCard(const StdMiniCard &) = delete;
    StdMiniCard(StdMiniCard &&) = delete;
    StdMiniCard & operator=(const StdMiniCard &) = delete;
    StdMiniCard & operator=(StdMiniCard &&) = delete;

    StdMiniCard& setData(std::string, CardData);
    int getData(std::string) const;
    StdMiniCard& setCaption(std::string, CardCaption);
    std::string getCaption(std::string) const;
    StdMiniCard& setLink(std::string, CardLink);
    CardLink getLink(std::string) const;

    StdMiniCard& setTag(std::string);
    StdMiniCard& removeTag(std::string);
    bool checkTag(std::string) const;

    StdMiniCard& setAction(std::string, CardFunction);

    CardAgrsPackage takeAction(std::string, CardAgrsPackage);

private:
    CardAgrsPackage self;
};
