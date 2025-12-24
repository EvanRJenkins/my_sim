#include "functiontable.h"

// Function table declaration
FunctionMapping_t g_FunctionTable[] = {
    { "SIN",    func_SIN },
    { "SQUARE", func_SQUARE },
    { "PULSE",  func_PULSE },
    { "DC",     func_DC },
    { "",       NULL }
};


// args[0] = Amplitude, args[1] = Angular Frequency (rad/s)
float func_SIN(float t, float args[]) {
    return args[0] * sinf(args[1] * t);
}

// args[0] = Amplitude, args[1] = Frequency (Hz)
float func_SQUARE(float t, float args[]) {
    // Simple square wave logic
    float period = 1.0f / args[1];
    float cyclePos = fmodf(t, period);
    if (cyclePos < period / 2.0f) return args[0];
    else return -args[0];
}

// args[0] = Amplitude, args[1] = Period, args[2] = Pulse Width
float func_PULSE(float t, float args[]) {
    float period = args[1];
    float width = args[2];
    if (fmodf(t, period) < width) return args[0];
    else return 0.0f;
}

// args[0] = DC Voltage
float func_DC(float t, float args[]) {
    return args[0];
}
