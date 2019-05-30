#include "Ebot.h"
#include "Ebot_bridge.h"

void setup()
{
    ebot_setup();
    bridge_setup();
    //Pin Modes
}

void loop()
{
    bridge_loop();
}
