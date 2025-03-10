#include <memory>
#include <mutex>

namespace ducktimer {
    class utils {
    public:
        static utils& getInstance();
        static void clearCurrentLine(int len);
        static void printPoint();
        static void setPointNums(const int& nums);
    private:
        static std::unique_ptr<utils> instance; // 智能指针只是用于对象的管理
        static std::mutex mtx;
        static int m_point_num;

    private:
        utils() = default;
        utils(const utils&) = delete;
        utils& operator=(const utils &)  = delete;
        ~utils() = default;
    };
}
