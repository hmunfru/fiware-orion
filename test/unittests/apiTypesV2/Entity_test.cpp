/*
*
* Copyright 2015 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* iot_support at tid dot es
*
* Author: Fermin Galan
*/

#include "apiTypesV2/Entity.h"
#include "unittest.h"

/* ****************************************************************************
*
* present - no output expected, just exercising the code
*/
TEST(Entity, present)
{
  utInit();

  Entity* enP    = new Entity();
  enP->id        = "E";
  enP->type      = "T";
  enP->isPattern = "false";

  ContextAttribute* caP = new ContextAttribute("A", "T", "val");
  enP->attributeVector.push_back(caP);

  enP->present("");

  utExit();
}


/* ****************************************************************************
*
* check
*/
TEST(Entity, check)
{
  ConnectionInfo ci;

  utInit();

  Entity* enP    = new Entity();
  enP->id        = "E";
  enP->type      = "T";
  enP->isPattern = "false";

  ContextAttribute* caP = new ContextAttribute("A", "T", "val");
  enP->attributeVector.push_back(caP);

  EXPECT_EQ("OK", enP->check(&ci, EntitiesRequest));

  enP->id = "";
  EXPECT_EQ("No Entity ID", enP->check(&ci, EntitiesRequest));

  enP->id = "E<1>";
  EXPECT_EQ("Invalid characters in entity id", enP->check(&ci, EntitiesRequest));
  enP->id = "E";

  enP->type = "T<1>";
  EXPECT_EQ("Invalid characters in entity type", enP->check(&ci, EntitiesRequest));
  enP->type = "T";

  enP->isPattern = "<false>";
  EXPECT_EQ("Invalid characters in entity isPattern", enP->check(&ci, EntitiesRequest));

  utExit();
}
