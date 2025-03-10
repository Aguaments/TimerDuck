#include "timer.h"

int main() {
    ducktimer::timer t(30, "test2.mp3"); // Default setting: 30 minutes
    t.run();
    return 0;
}
