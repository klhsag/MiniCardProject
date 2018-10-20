
#include "rolecard.h"

#include "../diyformat/myfwd.h"

using namespace rolecard;

void rolecard::rolecardInitialize(CardLink self, CardAgrsPackage args) {
	self->setAction("setRoleCaption", setRoleCaption);
	setRoleCaption(self, args);
	//self->setAction("setRoleBelonging", setRoleBelonging);
	//setRoleCaption(self.get(), args);
	self->setAction("setRoleMeasurement", setRoleMeasurement);
	setRoleMeasurement(self, args);
	self->setAction("appendMeasurementMsg", appendMeasurementMsg);
	self->setAction("sufferDamage", sufferDamage);
	self->setAction("isDying", isDying);
	self->setAction("dieTag", dieTag);
}

CardAgrsPackage rolecard::setRoleCaption(StdMiniCard * self, CardAgrsPackage args){
	self->setCaption("caption", args.caption["caption"]);
	return {};
}

CardAgrsPackage rolecard::setRoleMeasurement(StdMiniCard * self, CardAgrsPackage args) {
	auto dataMeasurements = split(args.caption["items"], "|");
	for (auto &str : dataMeasurements) {
		self->setData(str, args.data[str]);
	}
	return {};
}

CardAgrsPackage rolecard::appendMeasurementMsg(StdMiniCard * self, CardAgrsPackage args) {
	auto dataMeasurements = split(args.caption["items"], "|");
	for (auto &str : dataMeasurements) {
        int data = self->getData(str);
		args.caption["message"] += "\t" + str + ": " + ((data==INT_MIN)?(""):diytostr(data)) + self->getCaption(str) + "\n";
	}
	return args;
}

CardAgrsPackage rolecard::sufferDamage(StdMiniCard * self, CardAgrsPackage args) {
	int damage = args.data["damage_digit"];
	std::string tgt_caption = self->getCaption("caption");
	args.caption["message"] += "[player " + tgt_caption + "] suffers " + diytostr(damage) + " damage(s).\n";
	int hp = self->getData("health");
	hp -= damage;
	self->setData("health", hp);
	args.caption["message"] += "now, @player " + tgt_caption + " 's health point is " + diytostr(hp) + ".\n";
	if (hp <= 0) {
		return self->takeAction("isDying", args);
	}
	return args;
}

CardAgrsPackage rolecard::isDying(StdMiniCard * self, CardAgrsPackage args) {
	return self->takeAction("dieTag", args);
}

CardAgrsPackage rolecard::dieTag(StdMiniCard * self, CardAgrsPackage args) {
	self->setTag("die");
	args.caption["message"] += "<player " + self->getCaption("caption") + "> is died.\n";
	return args;
}
