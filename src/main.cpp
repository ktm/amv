//
// Created by ktm on 3/17/16.
//
#include "script/chaiscript_gateway.h"
#include "serial/serial.hxx"
#include "gps/gps.h"
#include "gps/nmea.h"

#include <chaiscript/chaiscript.hpp>
#include <ev.h>
#include <thread>

using serial_stream_ptr = std::shared_ptr<serial_stream>;
using serial_stream_ptr_vec = std::vector<serial_stream_ptr>;

serial_stream_ptr_vec serial_stream_vector;

//wrappers for chaiscript
void writeContextValue(std::string name, chaiscript::Boxed_Value value) {
    chaiscript_gateway::Instance().write_from_js(name, value);
}

int addStream(serial_stream_ptr p) {
    serial_stream_vector.push_back(p);
    return serial_stream_vector.size() - 1;
}

int serial_init(std::string portName) {
    auto ssp = std::make_shared<serial_stream>(portName, 9600);

    return addStream(ssp);
}

int serial_write(int serialId, std::string s) {
    unsigned char deviceNumber = 12;
    unsigned char channelNumber = 0;

    // Generate a sinusoid signal to send to the PololuInterface
    const float pi = 3.141592653589793f;
    const unsigned int channelMinValue = 4000;
    const unsigned int channelMaxValue = 8000;
    const unsigned int channelValueRange = channelMaxValue - channelMinValue;
    const unsigned int signalPeriodInMs = 2000;
    clock_t t;
    int f;
    t = clock();
    int timeSinceStart = t/CLOCKS_PER_SEC;

    for (int channelValue = channelMinValue; channelValue < channelMaxValue; channelValue+=50)
    {
        printf("\rchannelValue=%d", (unsigned int)channelValue );
        unsigned char command[4] = { 0x84, channelNumber, (unsigned char)(channelValue & 0x7F), (unsigned char)((channelValue >> 7) & 0x7F) };
        serial_stream_vector[serialId]->writeBytes(command, 4);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 1;
}

void update_gps_location(int serialId) {
    uint8_t gps_status = _EMPTY;
    while (gps_status != _COMPLETED) {
        gps_status = process_gps_location(serial_stream_vector[serialId]->readLine(), gps_status);
    }
}

void initChaiObjects() {
    chaiscript_gateway::Instance().registerFunction(writeContextValue, "writeContext");
    chaiscript_gateway::Instance().registerFunction(serial_init, "serialInit");
    chaiscript_gateway::Instance().registerFunction(serial_write, "serialWrite");
    chaiscript_gateway::Instance().registerFunction(update_gps_location, "updateGPS");
}

extern int mainTest();

ev_timer evTimer;
chaiscript::Boxed_Value scriptObject;
std::function<std::string(chaiscript::Boxed_Value &, const std::string &)> funcObject;

static void timer_cb (EV_P_ ev_timer *w, int revents)  {
    std::cout << "c++ timer_cb " << std::endl;

    auto result = funcObject(scriptObject, "timer bits");
}

int main (int argc, char *argv[]) {
    initChaiObjects();

    if (argc > 1) {
        auto obj = chaiscript_gateway::Instance().evaluateFile(std::string(argv[1]));

        scriptObject = chaiscript_gateway::Instance().js_context.eval("t");
        funcObject = chaiscript_gateway::Instance().js_context.eval<std::function<std::string(chaiscript::Boxed_Value &, const std::string &)>>("func");

        struct ev_loop *loop = EV_DEFAULT;
        ev_timer_init (&evTimer, timer_cb, 1., 5.);
        ev_timer_start (loop, &evTimer);
        ev_run (loop, 0);
    } else {
        mainTest();
    }

    return 0;
}

