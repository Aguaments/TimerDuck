#define BUFFER_SIZE 4096

namespace ducktimer {
    class tools {
    public:
        static void clearCurrentLine(int len);
        static void setIONewBuffer();
    private:
        static char ibuffer[BUFFER_SIZE];
        static char obuffer[BUFFER_SIZE];
    };
}
