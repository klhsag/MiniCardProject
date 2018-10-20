#pragma once

#include <memory>

#include "../cardlib/minicardmgr.h"

namespace rolecard{

void rolecardInitialize(CardLink self, CardAgrsPackage args);

CardAgrsPackage setRoleCaption(CardLink self, CardAgrsPackage args);
//CardAgrsPackage setRoleBelonging(StdMiniCard * self, CardAgrsPackage args);
CardAgrsPackage setRoleMeasurement(CardLink self, CardAgrsPackage args);
CardAgrsPackage appendMeasurementMsg(CardLink self, CardAgrsPackage args);
//CardAgrsPackage causeDamage(StdMiniCard * self, CardAgrsPackage args);
CardAgrsPackage sufferDamage(CardLink self, CardAgrsPackage args);
CardAgrsPackage isDying(CardLink self, CardAgrsPackage args);
CardAgrsPackage dieTag(CardLink self, CardAgrsPackage args);

}

