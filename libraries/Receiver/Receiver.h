/* Receiver.h
 *
 * Class for reading and interpretting PPM Input
 *
 * Sam McAnelly
 * Oklahoma State University
 * Spring 2019
 *
 */

#ifndef Receiver_h
#define Receiver_h

//#include "Arduino.h"

class Receiver {
    public:
        Receiver(int pin, bool *_active) {
            //set pin
            //pinMode(pin, INPUT_PULLUP);
            active = _active;
            channel_values = new int[6];
        }

        ~Receiver() {
            delete channel_values;
        }

        void update();
        int getChannelValue(int channel);

    private:
        bool *active;
        int *channel_values;
};

#endif