
#include <iostream>

#include "stdminicard.h"

StdMiniCard& StdMiniCard::setData(std::string index, int x){
    self.data[index] = x;
    return *this;
}

int StdMiniCard::getData(std::string tgt) const{
    auto it = self.data.find(tgt);
    if (it==self.data.end()) return 0; // or INT_MIN, not determined
    return it->second;
}

StdMiniCard& StdMiniCard::setCaption(std::string index, std::string c){
    self.caption[index] = c;
    return *this;
}

std::string StdMiniCard::getCaption(std::string tgt) const{
    auto it = self.caption.find(tgt);
    if (it==self.caption.end()) return "";
    return it->second;
}

StdMiniCard& StdMiniCard::setLink(std::string index, CardLink target){
    self.link[index] = target;
    return *this;
}

CardLink StdMiniCard::getLink(std::string tgt) const{
    auto it = self.link.find(tgt);
    if (it==self.link.end()) return CardLink(); //==std::weak_ptr<StdMiniCard>();
    return it->second;
}

StdMiniCard& StdMiniCard::setTag(std::string tag){
    setCaption(tag, tag);
    return *this;
}

StdMiniCard& StdMiniCard::removeTag(std::string tag){
    setCaption(tag, "");
    return *this;
}

bool StdMiniCard::checkTag(std::string tag) const{
    return getCaption(tag).size()>0;
}

StdMiniCard& StdMiniCard::setAction(std::string index, CardFunction func){
    self.func[index] = func;
    return *this;
}

CardAgrsPackage StdMiniCard::takeAction(std::string index, CardAgrsPackage args){
    auto it = self.func.find(index);
    if (it==self.func.end()) return {};
    return it->second(this, args); //强制转型为shared_ptr, 这里主要是为了兼容与便于拓展
}

