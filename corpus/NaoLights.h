#ifndef NaoLights_h_DEFINED
#define NaoLights_h_DEFINED

#include <pthread.h>

#include "Lights.h"
#include "dcmproxy.h"
#include "ALLedNames.h"
#include "NaoRGBLight.h"
/**
 *  This class implements LED capability on the Nao robot using the DCM in Naoqi
 *
 *  The basic design is to make a NaoRGBLight for each LED group.  That instance
 *  handles the creation of the appropropriatly formatted ALValue to send to
 *  the DCM low level.
 *
 *  Led groups can be referenced either by ID or by string name, through
 *  the latter is currently not as fast as it could be (TODO: fix that)
 *
 *  @author Johannes Strom
 *  @date June 2009
 */



class NaoLights : public Lights{
public:
    NaoLights(AL::ALPtr<AL::ALBroker> broker);
    virtual ~NaoLights();

public:
    void setRGB(const std::string led_id, const int newRgbHex);
    void setRGB(const unsigned int led_id, const int newRgbHex);

    void sendLights();
private:
    void generateLeds();
    void sendLightCommand(ALValue &command);
private:
    AL::ALPtr<AL::DCMProxy> dcmProxy;
    AL::ALValue leftFaceLedCommand;
    std::vector<NaoRGBLight*> ledList;
    std::vector<int> hexList;

    mutable pthread_mutex_t lights_mutex;
};

#endif
