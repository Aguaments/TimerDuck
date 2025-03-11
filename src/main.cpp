#include "timer.h"

int main() {
    ducktimer::timer t(30, "test1.mp3"); // Default setting: 30 minutes
    t.run();
    return 0;
}
