#include <memory>
#include <mutex>

namespace ducktimer {
    class utils {
    public:
        static utils& getInstance();
        void clearCurrentLine(int len);
        void printPoint();
        void setPointNums(const int& nums);
        int isYOrN();
    private:
        static std::unique_ptr<utils> instance; // 智能指针只是用于对象的管理
        static std::recursive_mutex mtx;
        int m_point_num;

    private:
        utils() = default;
        utils(const utils&) = delete;
        utils& operator=(const utils &)  = delete;
    };
}
